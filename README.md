# MakeBAX-Multi

Make .bax files from various filetypes!

Only windows supported for now!

# Requirements

Requires [ffmpeg](https://www.ffmpeg.org/download.html) **with the bin folder in PATH**. If you don't know what that is, and you've installed a .exe or .msi, it's probably ok. If it does not work, search for how to add to PATH, and add: "C:/yourpath/toffmpeg/bin"
In my case this is "C:\ffmpeg\bin", but it may change.
Another option is to have the file "ffmpeg.exe" **in the same folder** as MakeBAX-Multi. A search function that will search for the file inside the subfolders is planned but not yet implemented.

If you are using Linux, you probably know enough to be able to do it. (Oh wait, I forgot, Linux is not supported)

Requires [MakeBAX](https://gitlab.com/Wolfvak/BAX/tags/first_release), **in the same folder as the file you want to convert and in the same folder as MakeBAX-Multi OR in your PATH**, renamed as "makebax" (**not** case sensitive). I don't know if I'm allowed to share MakeBAX here, so just download it from there. It's a .exe that you just need to put on your folder.

# Usage

1. Make sure MakeBAX-Multi is in the same folder as MakeBAX.exe and the file you want to convert.
2. Open up cmd (not required but recommended) and cd to that folder
3. Double click on the program (or load it from cmd if you did step 2, just write the name of the program and press enter)
4. Follow on-screen instructions
5. Wait until the program has finished.
6. The .bax should be there. If there's anything not working tell me.
7. Profit!

# Building it

Browse to the /source/ folder and do "g++ main.cpp -o MakeBAX-Multi.exe -static-libgcc -static-libstdc++"
Easy.
