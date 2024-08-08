#include <iostream>
#include <fstream>
#include <zip.h>
#include <sys/stat.h> // For mkdir

int extractZip(const char* zipFile, const char* extractDir) {
    int err = 0;
    zip *z = zip_open(zipFile, 0, &err);
    if (z == nullptr) {
        std::cerr << "Error opening zip file: " << zip_strerror(z) << std::endl;
        return 1;
    }

    struct zip_stat st;
    zip_stat_init(&st);

    // Iterate over all entries in the zip file
    for (zip_uint64_t i = 0; i < zip_get_num_entries(z, 0); i++) {
        const char *fname = zip_get_name(z, i, 0); // Correct usage
        if (fname == nullptr) {
            std::cerr << "Error getting file name: " << zip_strerror(z) << std::endl;
            zip_close(z);
            return 1;
        }

        zip_stat(z, fname, 0, &st);
        if (st.valid & ZIP_STAT_NAME) {
            std::string filePath = std::string(extractDir) + "/" + fname;

            // Check if the entry is a directory by checking the size
            if (st.size == 0) {
                // It's a directory
                mkdir(filePath.c_str(), 0777);
            } else {
                // It's a file
                zip_file *f = zip_fopen(z, fname, 0);
                if (!f) {
                    std::cerr << "Error opening file in zip: " << fname << std::endl;
                    zip_close(z);
                    return 1;
                }

                std::ofstream fileOut(filePath, std::ios::binary);
                char buffer[1024];
                zip_int64_t len;
                while ((len = zip_fread(f, buffer, sizeof(buffer))) > 0) {
                    fileOut.write(buffer, len);
                }
                zip_fclose(f);
                fileOut.close();
            }
        }
    }
    zip_close(z);
    return 0;
}

int main() {
    extractZip("example.zip", "extracted_zip");
    return 0;
}