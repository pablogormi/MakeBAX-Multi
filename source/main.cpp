#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>


using namespace std;

bool fileExist(const string& fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}


int main() {
	system("echo off");
	char version[] = "1.1";
	string filename, outname, screen, framerate, outfile, cont;
	
	// ask for stuff
	cout << "BAX Converter v" << version << endl;
	if (!fileExist("makebax.exe")) {
		cout << "makebax.exe was not found!" << endl;
		cout << "you may continue, but ONLY if you know what you're doing. " << endl;
		cout << "if you don't know what this is, please follow the instructions again." << endl;
		cout << "if the problem persists, open an issue or message @unipablojorge in gbatemp." << endl;
		cout << "Do you want to continue? y/n" << endl;
		cin >> cont;
		if (cont != "y"){
			return 0;
		}
	}
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
	cout << "3. Both Screens" << endl;
	cout << "> ";
	cin >> screen;
	cout << "Select a framerate, recommended 60." << endl;
	cout << "> ";
	cin >> framerate;
	
	if (screen == "1") {
		screen = "400";
	} else if (screen == "2") {
		screen = "320";
	} else if (screen == "3") {
		screen = "720";
	} else {
		cout << "That's not a screen.";
		return 1;
	}
	
	// Check for .gif and kick you out of the program because I'm too lazy
	if (extension == "gif") {
		int repeat;
		cout << "Gif found! Can't convert directly to ivf. I'm going to have to convert it to mp4" << endl;
		
		// Loop the gif n stuff
		cout << "How many times do you want to loop the video? Recommended is 1 (no looping)." << endl;
		cin >> repeat;
		
		repeat -= 1;
		
		
		std::string s = std::to_string(repeat); 
		sleep(1);
		string gifcmd = "ffmpeg -stream_loop " + s + " -i " + filename + " -b:v 1M -r " + framerate + " " + outname + ".mp4";
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