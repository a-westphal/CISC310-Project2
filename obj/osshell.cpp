#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fstream>

/*void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}*/
 
void addToFile (std::string array[128], std::string input,bool clear);
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
        int num_print = 0;

        std::getline (std::cin,input);
        std::ifstream hist_file;
        hist_file.open("history.txt", std::fstream::in);

        int line_count = 0;
        std::string line; 
        std::string hist_arr[128];

        while(std::getline(hist_file,line))
        {
        	if(line_count < 128)
        	{
        		hist_arr[line_count] = line;
        	}
        	line_count++;
        }
        hist_file.close();

        //ends the history loop
        bool end = false;
        //makes sure we don't call addToFile() twice
        bool print = false;

		if(input == ""){ //Blank command
		}
    
        //if the input includes "history": 
        else if(input.find("history") >= 0 && input.find("history") <= input.length())
        {
            //to parse the input: 
            std::string space = " ";    

            if(input.find(space) > 0 && input.find(space) < input.length())
            {
                //the index to start looking for ints or chars: 
                int split = input.find(space);
                std::string half = input.substr(split+1, (input.length() - split));

                if(isalpha(half[0]))
                {
                    //letters
                    if(half.find("clear") != 0)
                    {
                        //error?
                        std::cout << "Error: history \"" << half << "\" command not found." <<std::endl;
                        end = true;
                    }

                    //otherwise we want to clear the history:
                    else
                    {
                    	end = true;
                    	print = true;
                    	addToFile(hist_arr,input,true);
                    }
                }

                else if(isdigit(half[0]) || half[0] == '-')
                {
                    //numbers
                    num_print = stoi(half);
                    if(num_print < 0)
                    {
                        //error
                        std::cout << "Error: history must have greater than 0 commands to print: " << num_print << std::endl;
                        end = true;
                    }
                }
            }

            if(num_print == 0 && !end)
            {
            	int count = 0;
                while(hist_arr[count]!= "" && count < 128)
                {
                	std::cout << count + 1 << ": " <<hist_arr[count] << std::endl;
                	count ++;
                } 
            }

            else if(num_print > 0 && !end)
            {
            	//print num_print times
                int counter = 0;
                int find = 0;
                bool finder = false;

                //find the last filled in index:
                while (!finder && find < 128)
                {
                	if(hist_arr[find].compare("") == 0)
                	{

                		finder = true;
                	}
                	find++;
                }
                while(counter < find -1)
                {
                    if(counter >= ((find-1) - num_print))
                    {
                       	std::cout << counter +1 <<": " <<hist_arr[counter] << std::endl;
                    } 
                    counter ++;
                }
            } 
            //add history to the end after history is printed
            if(!print)
            {	addToFile(hist_arr,input,false); }
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
        else if(input.find("exit") >= 0 && input.find("exit") <= input.length())
        {
            //end the program and loop
            done = true;
            addToFile(hist_arr,input,false);
        } else {

			char* currPath;
			char* commands;
			int spacePosition;

			spacePosition = input.find(" ");
			printf("%d is the position of the space\n", spacePosition);
			std::string command;
			std::string argument;

			if(spacePosition > 0){ //Argument was passed with command
				command = input.substr(0, spacePosition);
				argument = input.substr(spacePosition + 1, input.length());
			} else {
				command = input;
			}

			std::cout << command << " is command.\n";
			std::cout << argument << " is argument.\n";

			std::cout << os_path << "\n";

			currPath = strtok(os_path,":");
			while(currPath != NULL){
				printf("%s\n", currPath);

				DIR *dir;
				struct dirent *d;
				if((dir = opendir(currPath)) != NULL){
					while ((d = readdir(dir)) != NULL){
						//printf("%s\n", d->d_name);
						if(strcmp(d->d_name, command.c_str()) == 0){
							printf("Match has been found.\n");





							//pid_t child = fork();
							//execv(d->d_name + "/" + command);
						}	
					}
				}
				closedir (dir);
				currPath = strtok (NULL, ":");
			}
		}

		input = "";
    }
    return 0;
}

void addToFile (std::string array[128],std::string input, bool clear)
{
	std::ofstream hist_out;
    hist_out.open("history.txt", std::ofstream::out);

    if(hist_out.is_open() && clear == true)
    {
    	hist_out << "";  
    	hist_out.close();
    	/*int count = 0;  
    	while(count < 128)
    	{
    		array[count] ="";
    		count ++;
    	}    */   
    }
    else if(hist_out.is_open() && clear == false)
    {
	    int out_count = 0;
	    bool out = false;
	    while(!out)
	    {
		    if(array[out_count].compare("")==0)
		   	{
		       	//don't submit to history file
		       	out = true;
		       	hist_out << input << "\n";
		    }
		    else
		    {
		       	hist_out << array[out_count]<<"\n";
		    }
	       	out_count++;
	    }
	    hist_out.close();
	}
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
