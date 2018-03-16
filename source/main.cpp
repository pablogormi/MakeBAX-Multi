#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

bool fileExist(const string& fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}


int main() {
	char version[] = "1.0";
	string filename, outname, screen, framerate;
	
	// ask for stuff
	cout << "BAX Converter v" << version << endl;
	cout << "Enter file with extension, example: 'test.mp4'" << endl;
	cout << "> "; 
	cin >> filename;

	if (!fileExist(filename)){
		cout << "File doesn't exist. Aborting...";
		return 1;
	} 

	cout << "Enter output file name (no extension)" << endl;
	cout << "> ";
	cin >> outname;
	cout << "Select screen for the video" << endl;
	cout << "1. Top Screen" << endl;
	cout << "2. Bottom Screen" << endl;
	cout << "> ";
	cin >> screen;
	cout << "Select a framerate, recommended 60." << endl;
	cout << "> ";
	cin >> framerate;
	
	if (screen == "1") {
		screen = "720";
	} else if (screen == "2") {
		screen = "320";
	} else {
		cout << "That's not a screen.";
		return 1;
	}
	
	// Check stuff
	cout << "You want to convert " << filename << " to " << outname << endl;

	std::string::size_type idx;

	idx = filename.rfind('.');

	std::string extension = filename.substr(idx+1);
	
	cout << "Your file extension is " << extension << endl;


	string conversion = "ffmpeg -i " + filename + " -f ivf -vf scale=" + screen + ":240,fps=" + framerate + " " + outname + ".ivf";
	cout << "The command used will be: " << endl;
	cout << conversion << endl;
	
	// Unnecessary wait time :D
	sleep(1);
	
	cout << "Starting mp4 conversion with ffmpeg..." << endl;
	
	const char *command = conversion.c_str();
	
	system(command);

}