#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

string swapValues(string& name){
    string num;
    string ano;
    string mes;
    string dia;
    int i = 0;
    while (i < name.size() && name[i] != '_') num += name[i++];
    i++;
    while (i < name.size() && name[i] != '-') ano += name[i++];
    i++;
    while (i < name.size() && name[i] != '-') mes += name[i++];
    i++;
    while (i < name.size() && name[i] != '.') dia += name[i++];

    return dia + "-" +mes+"-"+ ano + "_"+num+".map";

}

void renameFiles(string& dirPath){
    string oldName; // num_aaaa-mm-dd.map
	string newName; // dd-mm-aaaa_num.map
	

    for (const auto & file : fs::directory_iterator(dirPath)){
        oldName = file.path().filename().generic_string();
        newName = swapValues(oldName);

        cout<< oldName<<"-----"<<newName<<endl;

        fs::path fileOldName = dirPath +"/"+ oldName;
        fs::path fileNewName =  dirPath +"/"+ newName;
        fs::rename(fileOldName, fileNewName);
    }
}



int main(){
    
    string dirPath = "./teste";
    
    renameFiles(dirPath);

}