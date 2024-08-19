// CPP
// Note: C++ does not have a built-in MongoDB driver. You need to use a third-party library like mongocxx.
// This example uses mongocxx.
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

int main() {
    // Create a connection
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);

    // Create a database
    auto database = client["test-database"];

    // Create a collection
    auto collection = database["test-collection"];

    // Insert a document
    bsoncxx::builder::stream::document document{};
    document << "name" << "John" << "age" << 30;
    collection.insert_one(document.view());

    // Read a document
    //error: no matching function for call to ‘mongocxx::v_noabi::collection::find_one(bsoncxx::detail::requires_not_t<bsoncxx::v_noabi::builder::stream::key_context<>, bsoncxx::detail::is_invocable<const char (&)[5], bsoncxx::v_noabi::builder::stream::single_context> >)’
    // auto result = collection.find_one(bsoncxx::builder::stream::document{} << "name" << "John");
    auto result = collection.find_one(bsoncxx::builder::stream::document{} << "name" << "John" << bsoncxx::builder::stream::finalize);

    if (result) {
        std::cout << bsoncxx::to_json(*result) << std::endl;
    }

    // Update a document
    bsoncxx::builder::stream::document update_document{};
    update_document << "$set" << bsoncxx::builder::stream::document{} << "age" << 31;
    // collection.update_one(bsoncxx::builder::stream::document{} << "name" << "John", update_document.view());
    collection.update_one(bsoncxx::builder::stream::document{} << "name" << "John" << bsoncxx::builder::stream::finalize, update_document.view());

    //error: no matching function for call to ‘mongocxx::v_noabi::collection::delete_one(bsoncxx::detail::requires_not_t<bsoncxx::v_noabi::builder::stream::key_context<>, bsoncxx::detail::is_invocable<const char (&)[5], bsoncxx::v_noabi::builder::stream::single_context> >)’
    // Delete a document
    // collection.delete_one(bsoncxx::builder::stream::document{} << "name" << "John");
    collection.delete_one(bsoncxx::builder::stream::document{} << "name" << "John" << bsoncxx::builder::stream::finalize);

    return 0;
}