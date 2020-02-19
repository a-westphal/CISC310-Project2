#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
 
std::vector<std::string> splitString(std::string text, char d);
std::string getFullPath(std::string cmd, const std::vector<std::string>& os_path_list);
bool fileExists(std::string full_path, bool *executable);

int main (int argc, char **argv)
{
    std::string input;
    char* os_path = getenv("PATH");
    std::vector<std::string> os_path_list = splitString(os_path, ':');
    bool done = false;

    std::cout << "Welcome to OSShell! Please enter your commands ('exit' to quit)." << std::endl;
    while(!done)
    {
        std::cout <<"osshell> ";
        std::getline (std::cin,input);
    
        //if the input includes "history": 
        if(input.find("history") >= 0 && input.find("history") <= input.length())
        {
            //the string history is here! 
            std::cout << "The word history is in your input!" << std::endl;
            for(int i = 0; i < input.length(); i ++)
            {
                
            }
        }
        // Repeat:
        //  Print prompt for user input: "osshell> " (no newline)
        //  Get user input for next command
        //  If command is `exit` exit loop / quit program
        //  If command is `history` print previous N commands
        //  For all other commands, check if an executable by that name is in one of the PATH directories
        //  If yes, execute it
        //  If no, print error statement: "<command_name>: Error running command" (do include newline)

        //if the input is "exit": 
        if(input.find("exit") >= 0 && input.find("exit") <= input.length())
        {
            //end the program and loop
            done = true;
        }

		char* currPath;
		currPath = strtok(os_path,":");
		while(currPath != NULL){
			printf("%s\n", currPath);
			currPath = strtok (NULL, ":");
		}
    }

    return 0;
    return 0;
}

// Returns vector of strings created by splitting `text` on every occurance of `d`
std::vector<std::string> splitString(std::string text, char d)
{
    std::vector<std::string> result;

    return result;
}

// Returns a string for the full path of a command if it is found in PATH, otherwise simply return ""
std::string getFullPath(std::string cmd, const std::vector<std::string>& os_path_list)
{
    return "";
}

// Returns whether a file exists or not; should also set *executable to true/false 
// depending on if the user has permission to execute the file
bool fileExists(std::string full_path, bool *executable)
{
    *executable = false;
    return false;
}
