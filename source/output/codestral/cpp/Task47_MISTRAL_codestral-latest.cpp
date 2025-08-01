#include <iostream>
#include <string>
#include <sqlite3.h>
#include <curl/curl.h>
#include <gumbo.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void scrapeAndStoreWebsiteData() {
    sqlite3* db;
    char* zErrMsg = nullptr;
    int rc;

    // Open SQLite DB
    rc = sqlite3_open("website_data.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Create table if not exists
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS data(title TEXT, link TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    // Fetch page using curl
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    // Parse HTML using gumbo
    GumboOutput* output = gumbo_parse(readBuffer.c_str());

    // Example: Extract title of the document
    GumboNode* root = output->root;
    std::string title = "Untitled";
    std::string link = "http://example.com";

    if (root->type == GUMBO_NODE_ELEMENT && root->v.element.tag == GUMBO_TAG_HTML) {
        GumboVector* children = &root->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            GumboNode* child = static_cast<GumboNode*>(children->data[i]);
            if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD) {
                GumboVector* headChildren = &child->v.element.children;
                for (unsigned int j = 0; j < headChildren->length; ++j) {
                    GumboNode* headChild = static_cast<GumboNode*>(headChildren->data[j]);
                    if (headChild->type == GUMBO_NODE_ELEMENT && headChild->v.element.tag == GUMBO_TAG_TITLE) {
                        if (headChild->v.element.children.length > 0) {
                            GumboNode* textNode = static_cast<GumboNode*>(headChild->v.element.children.data[0]);
                            if (textNode->type == GUMBO_NODE_TEXT) {
                                title = textNode->v.text.text;
                            }
                        }
                    }
                }
            }
        }
    }
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    // Insert into SQLite
    const char* insertSQL = "INSERT INTO data(title, link) VALUES(?, ?);";
    sqlite3_stmt* stmt = nullptr;
    rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare insert statement." << std::endl;
    } else {
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, link.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert data." << std::endl;
        } else {
            std::cout << "Data inserted successfully: " << title << " | " << link << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
}
