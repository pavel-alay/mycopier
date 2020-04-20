#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

static const char* TIMESTAMP_TEMPLATE = "/last-";

void timestamp(const string& targetDir, bool isFail) {
    const std::time_t time_now = std::time(nullptr);
    string timestamp = targetDir + TIMESTAMP_TEMPLATE;
    for (const auto &entry : fs::directory_iterator(targetDir)) {
        if (entry.path().string().starts_with(timestamp)) {
            if (!fs::remove(entry.path())) {
                cerr << "[FAIL] " << entry.path() << ": fail during remove\n";
            }
            break;
        }
    }
    if (isFail)
        timestamp += "fail-";
    std::stringstream ss;
    ss << put_time(localtime(&time_now), "%Y-%m-%d %OH.%OM.%OS");
    timestamp += ss.str();

    if (isFail)
        cout << "[FAIL] Last update: " + ss.str() << endl;
    else
        cout << "[OK] Last update: " + ss.str() << endl;
    ofstream outfile (timestamp);
    outfile.close();
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Options: targetDir sourceFile1 sourceFile2 ..." << endl;
        return 1;
    }
    int filesCount = argc - 2;
    string targetDir = argv[1];
    bool isFail = false;
    for (int i = 0; i < filesCount; ++i) {
        fs::path source = argv[i + 2];
        fs::path target = targetDir + "/" + source.filename().string();
        try {
            if (!fs::copy_file(source, target, fs::copy_options::overwrite_existing)) {
                cerr << "[FAIL] " << source << ": coping failed";
                isFail = true;
            }
        } catch(fs::filesystem_error& e) {
            cerr << "[FAIL] Could not copy file: " << e.what() << endl;
            isFail = true;
            break;
        }
    }

    timestamp(targetDir, isFail);
    return 0;
}
