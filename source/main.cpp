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
	system("echo off");
	char version[] = "1.1";
	string filename, outname, screen, framerate, outfile;
	
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
	
	//Check for .ivf file
	std::string::size_type idx;
	idx = filename.rfind('.');
	std::string extension = filename.substr(idx+1);
	cout << "Your file extension is " << extension << endl;
	
	if (extension == "ivf") {
		outfile = filename;
		string baxcomm = "makebax " + outfile + " " + outname + ".bax";
		string res;
		cout << "IVF file found! Is the resolution correct? " << endl;
		cout << "y/n > ";
		cin >> res;
		if (res == "y") {
			cout << "Ok, skipping ffmpeg and using MakeBAX..." << endl;
			cout << "Command to be used: " << baxcomm << endl;
			sleep(1);
			system(baxcomm.c_str());
			return 0;
		} else if (res == "no") {
			cout << "Ok, putting it through ffmpeg... ";
			sleep(1);
		}
	}
	
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
	
	// Check for .gif and kick you out of the program because I'm too lazy
	if (extension == "gif") {
		cout << "Gif found! Can't convert directly to ivf. Converting to mp4... " << endl;
		sleep(1);
		string gifcmd = "ffmpeg -i " + filename + " -b:v 1M -r " + framerate + " " + outname + ".mp4";
		system(gifcmd.c_str());
		system("cls");
		cout << " " <<endl;
		cout << " " <<endl;
		cout << " " <<endl;
		cout << "I've converted " << filename << " to a MP4 file." << endl;
		cout << "Please run this program again but using " << outname << ".mp4 as input. Thank you!";
		
		return 0;
	}
	
	// Check stuff
	cout << "You want to convert " << filename << " to " << outname << ".bax" << " at " << framerate << " fps." << endl;

	
	// Remind me of adding comments

	
	outfile = outname + ".ivf";
	string baxcomm = "makebax " + outfile + " " + outname + ".bax";
	string conversion = "ffmpeg -i " + filename + " -f ivf -vf scale=" + screen + ":240,fps=" + framerate + " " + outname + ".ivf";
	cout << "The command used will be: " << endl;
	cout << conversion << endl;
	cout << "Starting mp4 conversion with ffmpeg..." << endl;
	
	// Unnecessary wait time :D
	sleep(1);
	
	const char *command = conversion.c_str();
	
	system(command);
	
	cout << "Conversion to .ivf finished! starting conversion to .bax..." << endl;
	cout << "Command to be used: " << baxcomm << endl;
	sleep(1);
	system(baxcomm.c_str());
	remove(outfile.c_str());
	
	cout << "Done! Your output file is named " << outname << ".bax!" << endl;
	system("pause");
	return 0;
}