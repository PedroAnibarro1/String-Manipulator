/***************************************************************
*   				Author: Pedro Anibarro					   *
*        				Trabajo Final     					   *
*      		 	Problem 1: String Manipulator     			   *
****************************************************************/


# include <iostream> //library to use cout and cin functions
# include <string> //library to work with strings
# include <fstream> //library to work with files
# include <ctime> //library to get the actual date and time
using namespace std;



/*********************** PROTOTIPOS *************************/
void getSave(string&, fstream&, bool&); //check if user wants to save the outputs and work with the file
void print(string, fstream&); //print in the file the console output
void getString(string&); //ask the user for the string 
void menu(string&, string&, fstream&, bool&); //shows and work with the menu
bool validSel(char); //validates the selection for the menu to be a valid char
void printOriginal(string, fstream&, bool); //print the original string without modification
void printUpper(string, fstream&, bool); //print the entered string all in uppercase
void printLower(string, fstream&, bool); //print all the string in Lowercase
void reverse(string, fstream&, bool); //change every character in the multiline string into its case inverse
void printUpperFirst(string, fstream&, bool); //print the string with the first character of each word in uppercase




/*********************** MAIN *************************/
 

int main(){
	
	//variables
	fstream file; //hold the file used to save all the outputs
	string filename; //contain the file path
	string phrase; //contain the string to be manipulated
	bool output; //contain the desicion of the user to save or not

	//proccess
	getSave(filename, file, output);
	cout<< endl;
	getString(phrase);
	menu(phrase, filename, file, output);


	return 0;
}


/*********************** FUNCTIONS *************************/


void getSave(string &filename, fstream &file, bool &output){

	//variables
	char choice; //hold the choice of saving the output
	bool error = false; //hold a boolean for an error 
	char dummy; //this variable is used for many things as reciclable to not waste memory
	
	//proccess


	do{
	//check if user wants to save
		do{
			cout<< "Want to save all your console outputs?\n" <<
					"\t1) Yes \n" <<
					"\t2) No \n";
			cin.get(choice);
			cin.ignore();
			system("clear");
		}while(choice != '1' && choice != '2');



		//if true ask for the file name and check if it already exist
		if(choice == '1'){
			
			output = true;

			//ask name file
			cout<< endl;
			cout<< "Which name you want for your file? \n";
			getline(cin, filename);

			//creates the path for the file
			filename = "/Users/P3LL0/Google Drive/Turabo/Clases UT/Cuarto Semestre/Intermediate Programming/Trabajo Final/stringmanipulator/" + filename;

			//open the file in input mode
			file.open(filename, ios::in);


			//checks if there is something inside the file

			//Yes? - close the file and ask to overwrite the file
			if(file >> dummy){
				file.close();
				file.clear();

				//overwrite?
				do{
					cout<< "Do you want to overwrite the file?\n" << 
							"\t1) Yes\n" << 
							"\t2) No\n";
					cin>> dummy;
					cin.ignore();
				}while(dummy != '1' && dummy != '2');

				//Yes? - open the file and overwrite the file
				if(dummy == '1'){
					file.open(filename, ios::out);
					cout<< "File overwrited." << endl;

				//No? - open the file and continue writing in the end
				}else{ 
					file.open(filename, ios::out | ios::app);
				}

			//No? - creates a file with the filename asked 
			}else{
				file.open(filename, ios::out | ios::app);
			}


			//checks if the file has open correctly 
			if(!file.fail()){
				error = false;


				//get the current day and time and print it on the file
				time_t rawtime;
  				time (&rawtime);
				file<< (ctime (&rawtime)) << endl;

			//No? - tells the user there was an error
			}else{ 
				error = true;
				cout<< "Error while opening the file.\n";
			}

		//choice is false - put the decision on variable output and close the file.
		}else{
			output = false;
			file.close();
		}

	}while(error && choice != '2'); //keep in the loop while throwing an error opening the file

	return;
}


/**********************************************************************/


void print(string sentence, fstream &file){

	//print the console output that another fuction sends
	file<< endl << sentence << endl << endl;

	return;
}

/**********************************************************************/

void getString(string &phrase){

	cout<< endl;

	//gets the string from the user
	do{
		cout<< "Enter a string: ";
		getline(cin, phrase);
	}while(phrase == "");

	return;
}

/**********************************************************************/

void menu(string &phrase, string &filename, fstream &file, bool &output){

	//variables
	char sel; //hold the selection of the menu that user enters
	string dummy; //this variable is used for many things as reciclable to not waste memory


	//do all the proccess while the user dont choose exit
	do{
		//checks if the output option is true and made a string depending
		if(output){
			dummy = "true";
		}else{
			dummy = "false";
		}

		//show menu and loop while the input is invalid
		do{
			system("clear");
			cout<< "Menu:\tString: " << phrase << endl << endl <<
					"\t1)Print Original\n" <<
					"\t2)Print Upper\n" << 
					"\t3)Print Lower\n" << 
					"\t4)Reverse\n" << 
					"\t5)Print Upper First\n" <<
					"\t6)Enter a different string\n" <<
					"\t7)Save outputs: " << dummy << endl <<
					"\t8)Exit\n";
			cin.get(sel);
			cin.ignore();
		}while(!validSel(sel));

		//according to the selection on the menu call the corresponding function
		switch(sel){
			case '1':
				printOriginal(phrase, file, output);
				break;
			case '2':
				printUpper(phrase, file, output);
				break;
			case '3':
				printLower(phrase, file, output);
				break;
			case '4':
				reverse(phrase, file, output);
				break;
			case '5':
				printUpperFirst(phrase, file, output);
				break;
			case '6':
				getString(phrase);
				break;
			case '7':
				if(!file.fail()){
					file.close();
				}
				getSave(filename, file, output);
				break;
			default:
				return;
		}

		cout<< endl << endl;

		//this switch is for the Press any key to continue
		switch(toupper(sel)){
			case '6':
			case '7':
				break;
			default:
				cout<< "Enter any key to continue...";
				getline(cin, dummy);
		}
	}while(sel != '8');



	return;
}

/**********************************************************************/

bool validSel(char sel){

	//checks if the selection is from 1 to 8
	switch(toupper(sel)){
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			return true;
		default:
			return false;
	}
}

/**********************************************************************/

void printOriginal(string phrase, fstream &file, bool output){

	cout<< endl << endl << "Original string: " << phrase;

	//if the output option to file is true send the whole sentence to be saved in the file
	if(output){
		string sentence = "Original string: " + phrase; //variable that store the sentence to be saved
		print(sentence, file);
	}

	return;
}

/**********************************************************************/

void printUpper(string phrase, fstream &file, bool output){

	string dummy = ""; //variable used to save the modified string temporarily

	cout<< endl << endl << "String with uppercases: ";

	//convert all the characters to uppercases
	for(int x = 0; x < phrase.length(); x++){
		dummy += toupper(phrase[x]);
		cout<< dummy[x];
	}

	//if the output option to file is true send the whole sentence to be saved in the file
	if(output){
		string sentence = "String with uppercases: " + dummy; //variable that store the sentence to be saved
		print(sentence, file);
	}

	return;
}

/**********************************************************************/

void printLower(string phrase, fstream &file, bool output){

	string dummy = ""; //variable used to save the modified string temporarily

	cout<< endl << endl << "String with lowercases: ";

	//convert all the characters to lowercases
	for(int x = 0; x < phrase.length(); x++){
		dummy += tolower(phrase[x]);
		cout<< dummy[x];
	}

	//if the output option to file is true send the whole sentence to be saved in the file
	if(output){
		string sentence = "String with lowercases: " + dummy; //variable that store the sentence to be saved
		print(sentence, file);
	}

	return;
}

/**********************************************************************/

void reverse(string phrase, fstream &file, bool output){

	string dummy = ""; //variable used to save the modified string temporarily


	cout<< endl << endl << "String in reverse: ";

	//reverse all the characters - if upper then convert to lower, and if lower then convert it to upper case
	for(int x = 0; x < phrase.length(); x++){
		if(isalpha(phrase[x])){
			if(islower(phrase[x])){
				dummy += toupper(phrase[x]);
				cout<< (dummy[x]);
			}else{
				dummy += tolower(phrase[x]);
				cout<< dummy[x];
			}
		}else{
			dummy += phrase[x];
			cout<< phrase[x];
		}
	}

	//if the output option to file is true send the whole sentence to be saved in the file
	if(output){
		string sentence = "String in reverse: " + dummy; //variable that store the sentence to be saved
		print(sentence, file);
	}



	return;
}

/**********************************************************************/

void printUpperFirst(string phrase, fstream &file, bool output){

	bool flag = true; //boolean that holds if a space is detected
	string dummy = ""; //variable used to save the modified string temporarily

	cout<< endl << endl << "String with first in upper: ";

	//put in upper case only the first letter of a word
	for(int x = 0; x < phrase.length(); x++){
		if(phrase[x] == ' '){
			flag = true;
			dummy += phrase[x];
			cout<< phrase[x];
		}else if(flag){
			dummy += toupper(phrase[x]);
			cout<< dummy[x];
			flag = false;
		}else{
			dummy += phrase[x];
			cout<< phrase[x];
		}
	}

	//if the output option to file is true send the whole sentence to be saved in the file
	if(output){
		string sentence = "String with first in upper: " + dummy; //variable that store the sentence to be saved
		print(sentence, file);
	}

	return;
}
