#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <set>
#include "json.hpp"
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;
using json = nlohmann::json;

vector<string> files;

std::string Recursive(std::string folder) {
    std::string search_path = folder.c_str();
    std::string search_path_ = search_path;
    search_path_ += "/*.*";
    search_path = search_path_;
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    std::string tmp;
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (!(!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))) {
                    tmp = folder + "\\";
                    tmp = tmp + fd.cFileName;
                    Recursive(tmp);
                }
            }
            else {
                std::string FinalFilePath = folder + "\\" + fd.cFileName;
                files.push_back(FinalFilePath);
            }

        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return folder;
}

bool has_suffix(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}



int main(){
std::string folder;
    cout << "Enter folder path : ";
    cin >> folder;
    cout << "\n\n";
    Recursive(folder);

    vector<string> jsonfiles;
    vector<string> otherfiles;
    vector<string> unfoundfiles;

    set<string> jsonset;
    set<string> unfoundset;

    map<string, string> jsonmap;

    std::string t;
    uint32_t count_json = 0, count = 0;
    while (!files.empty()) {
        t = files.back();
        if (has_suffix(t, ".json")) {
            count_json++;
            jsonfiles.push_back(t);
            t.clear();
        }
        else {
            count++;
            otherfiles.push_back(t);
            t.clear();
        }
        files.pop_back();
    }

    for (auto i : otherfiles) {
        std::string temp2 = i.substr(i.find_last_of("\\") + 1);

        for (auto j : jsonfiles) {
            if (j.find(temp2) != std::string::npos) {
                jsonmap[i] = j;
                break;
            }
        }     
        if (jsonmap.find(i) == jsonmap.end()) {
            unfoundfiles.push_back(i);
        }   
    }

    CreateDirectoryW(L"E:\\new_google_2", NULL);

    uint32_t count_unfound = 0;

    for (auto i : jsonmap) {
        std::ifstream f(i.second);
        json data = json::parse(f);
        string datetime = data["creationTime"]["timestamp"]
            .get<std::string>();

        time_t t = std::stoi(datetime);

        std::tm* ptm = std::localtime(&t);
        // convert to IST
        ptm->tm_hour += 5;
        ptm->tm_min += 30;
        std::mktime(ptm);

        // Format: Mo, 15-06-2009 202000
        char buffer[32];
        std::strftime(buffer, 32, "%d-%m-%Y %H%M%S", ptm);
        std::string name_datetime(buffer);

        {
            // check if file name is IMG or VID
            // if img then add .jpg to the end else add .mp4
            if (i.first.find(".jpg") != std::string::npos) {
                name_datetime += ".jpg";
            }
            else if (i.first.find(".mp4") != std::string::npos) {
                name_datetime += ".mp4";
            }
            else if (i.first.find(".jpeg") != std::string::npos) {
                name_datetime += ".jpeg";
            }
            else if (i.first.find(".png") != std::string::npos) {
                name_datetime += ".png";
            }
            else if (i.first.find(".gif") != std::string::npos) {
                name_datetime += ".gif";
            }
            else if (i.first.find(".webp") != std::string::npos) {
                name_datetime += ".webp";
            }
            else if (i.first.find(".bmp") != std::string::npos) {
                name_datetime += ".bmp";
            }
            else if (i.first.find(".heic") != std::string::npos) {
                name_datetime += ".heic";
            }
            else if (i.first.find(".heif") != std::string::npos) {
                name_datetime += ".heif";
            }
            else if (i.first.find(".tiff") != std::string::npos) {
                name_datetime += ".tiff";
            }
            else if (i.first.find(".raw") != std::string::npos) {
                name_datetime += ".raw";
            }
            else if (i.first.find(".arw") != std::string::npos) {
                name_datetime += ".arw";
            }
            else if (i.first.find(".cr2") != std::string::npos) {
                name_datetime += ".cr2";
            }
            else if (i.first.find(".nrw") != std::string::npos) {
                name_datetime += ".nrw";
            }
            else if (i.first.find(".orf") != std::string::npos) {
                name_datetime += ".orf";
            }
            else if (i.first.find(".rw2") != std::string::npos) {
                name_datetime += ".rw2";
            }
            else if (i.first.find(".rwl") != std::string::npos) {
                name_datetime += ".rwl";
            }
            else if (i.first.find(".dng") != std::string::npos) {
                name_datetime += ".dng";
            }
            else if (i.first.find(".nef") != std::string::npos) {
                name_datetime += ".nef";
            }
            else if (i.first.find(".raf") != std::string::npos) {
                name_datetime += ".raf";
            }
            else if (i.first.find(".x3f") != std::string::npos) {
                name_datetime += ".x3f";
            }
            else if (i.first.find(".JPG") != std::string::npos) {
                name_datetime += ".JPG";
            }
            else if (i.first.find(".mov") != std::string::npos) {
                name_datetime += ".mov";
            }
            else if (i.first.find(".3gp") != std::string::npos) {
                name_datetime += ".3gp";
            }
            
            else {
                cout << "\n" << count_unfound++ << "\nError in file : " << i.first << endl;
            }
        }

        // first check if same file name exists in the new folder
        // if yes then add a number to the end of the file name
        // else copy the file to the new folder
        if (std::filesystem::exists("E:\\new_google_2\\" + name_datetime)) {
            uint32_t count = 1;
            std::string temp = name_datetime;
            while (std::filesystem::exists("E:\\new_google_2\\" + temp)) {
                temp = name_datetime;
                temp = temp.erase(temp.find_last_of("."), temp.length());
                temp += "(" + std::to_string(count) + ")";
                temp += name_datetime.substr(name_datetime.find_last_of("."), name_datetime.length());
                count++;
            }
            name_datetime = temp;
        }
        std::filesystem::copy(i.first, "E:\\new_google_2\\" + name_datetime, std::filesystem::copy_options::none);
    }
    
    for (auto i : unfoundfiles) {
        string temp2 = i.substr(i.find_last_of("\\") + 1);
        // if file is of the form IMG_20200101_123456.jpg
        // or IMG_20200101_123456_HDR.jpg
        // or VID_20200101_123456.mp4
        // or VID_20200101_123456_HDR.mp4
        // or IMG_20200101_123456_BURST001.jpg
        // or IMG-20200101-WA0001.jpg
        // or IMG-20200101-WA0001_HDR.jpg
        // or Screenshot_2018-04-04-15-19-58.png
        // or Screenshot_2018-04-04-15-19-58-1.png
        // or PANO_20230323_131337.jpg
        // 20200205_152403.jpg
        // then extract the date and time from the file name
        // and rename the file accordingly
        std::string datetime;
        if (temp2.find("IMG_") != std::string::npos || temp2.find("VID_") != std::string::npos) {
            datetime = temp2.substr(temp2.find("_") + 1);
            datetime = datetime.substr(0, datetime.find("."));
        }
        else if (temp2.find("IMG-") != std::string::npos) {
            datetime = temp2.substr(temp2.find("-") + 1);
            datetime = datetime.substr(0, datetime.find("."));
        }
        else if (temp2.find("VID-") != std::string::npos) {
            datetime = temp2.substr(temp2.find("-") + 1);
            datetime = datetime.substr(0, datetime.find("."));
        }
        else if (temp2.find("Screenshot_") != std::string::npos) {
            datetime = temp2.substr(temp2.find("_") + 1);
            datetime = datetime.substr(0, datetime.find("."));
        }
        else if (temp2.find("PANO_") != std::string::npos) {
            datetime = temp2.substr(temp2.find("_") + 1);
            datetime = datetime.substr(0, datetime.find("."));
        }
        else {
            datetime = temp2.substr(0, temp2.find("."));
            cout << "\n\nUnfound file : " << i << endl;
            cout << "\n\nUnfound file : " << temp2 << endl;
        }

        try{
            if (datetime.substr(0, 6).find('-') == std::string::npos) {
                datetime = datetime.substr(0, 4) + "-" + datetime.substr(4, 2) + "-" + datetime.substr(6, 2) + datetime.substr(8, datetime.length());
            }
        } catch (std::exception& e) {
            cout << "\nFile shorter than len 6 " << i << endl;
        }
        datetime += temp2.substr(temp2.find_last_of("."), temp2.length());


        // copy the file to the new folder
        // first check if same file name exists in the new folder
        // if yes then add a number to the end of the file name
        // else copy the file to the new folder
        if (std::filesystem::exists("E:\\new_google_2\\" + datetime + i.substr(i.find_last_of("."), i.length()))) {
            uint32_t count = 1;
            std::string temp = datetime;
            while (std::filesystem::exists("E:\\new_google_2\\" + temp + i.substr(i.find_last_of("."), i.length()))) {
                temp = datetime;
                temp = temp.erase(temp.find_last_of("."), temp.length());
                temp += "(" + std::to_string(count) + ")";
                temp += datetime.substr(datetime.find_last_of("."), datetime.length());
                count++;
            }
            datetime = temp;
        }

        std::filesystem::copy(i, "E:\\new_google_2\\" + datetime + i.substr(i.find_last_of("."), i.length()), std::filesystem::copy_options::none);

    }


    cout << "\n\nCount : " << count << endl << "Count_json : " << count_json << endl;

    
return 0;
}