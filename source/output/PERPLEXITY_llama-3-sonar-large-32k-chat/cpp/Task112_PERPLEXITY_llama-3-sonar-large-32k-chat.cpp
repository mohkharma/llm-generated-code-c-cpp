#include <mongoc/mongoc.h>
#include <bson/bson.h>
#include <iostream>

int main() {
    // Initialize the MongoDB C driver
    mongoc_init();

    mongoc_client_t *client;
    mongoc_collection_t *collection;
    bson_t *doc;

    // Create client and collection
    client = mongoc_client_new("mongodb://localhost:27017/");
    collection = mongoc_client_get_collection(client, "mydatabase", "mycollection");

    // Create a document
    doc = bson_new();
    BSON_APPEND_UTF8(doc, "name", "John");
    BSON_APPEND_INT32(doc, "age", 30);
    mongoc_collection_insert_one(collection, doc, NULL, NULL, NULL);
    bson_destroy(doc);

    // Read documents
    bson_t *filter;
    filter = bson_new();
    BSON_APPEND_UTF8(filter, "name", "John");
    mongoc_cursor_t *cursor;
    cursor = mongoc_collection_find_with_opts(collection, filter, NULL, NULL);
    const bson_t *doc_read;
    while (mongoc_cursor_next(cursor, &doc_read)) {
        char *str = bson_as_json(doc_read, NULL);
        std::cout << str << std::endl; // Print the document as JSON
        bson_free(str); // Free the JSON string
    }
    bson_destroy(filter);
    mongoc_cursor_destroy(cursor);

    // Update document
    bson_t *update;
    update = bson_new();
    bson_t *set_doc = bson_new(); // Create a new document for the update
    BSON_APPEND_INT32(set_doc, "age", 31);
    BSON_APPEND_DOCUMENT(update, "$set", set_doc); // Use $set operator
    bson_destroy(set_doc); // Free the temporary document


    //error: too few arguments to function ‘bool mongoc_collection_update_one(mongoc_collection_t*, const bson_t*, const bson_t*, const bson_t*, bson_t*, bson_error_t*)’
    // mongoc_collection_update_one(collection, filter, update, NULL, NULL);
    mongoc_collection_update_one(collection, filter, update, NULL, NULL, NULL);
    bson_destroy(update);

    // Delete document
    //error: too few arguments to function ‘bool mongoc_collection_delete_one(mongoc_collection_t*, const bson_t*, const bson_t*, bson_t*, bson_error_t*)’
    // mongoc_collection_delete_one(collection, filter, NULL, NULL);
    mongoc_collection_delete_one(collection, filter, NULL, NULL, NULL);
    bson_destroy(filter);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);

    // Cleanup
    mongoc_cleanup();

    return 0;
}