/*
    Music Collection Searcher - From a tab separated file, read data on an artists name, genres, active years, and discography.
            Search by user given keyword through artist name, genre, track title, & active year and display relevant data
*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct musicCollection{//Struct to hold music collection
    int capacity = 3;//Set capacity of artist array - Used to define the number of artists in loops 
    string name;//Artist name
    int yearStart, yearEnd, genreNum, discographyNum;//Year artist started & ended - Number of genres - Number of tracks
    int* yearRange = new int[1];//Year range array to hold every year a artist has preformed
    string* genre = new string[1];//Genre array to hold every genre a artist can fall under
    string* discographyTrack = new string[1];//Track title array to hold every song in the discography file
    int* discographyTrackYear = new int[1];//Song year parallel (parallel w/ track) array 
};

string* resizeGenre(string array[], int capacity){//Resize array by creating a new temp array and returning the new arrays pointer value
    string* tempGenre = new string[capacity];//New array with new bigger capacity  
    delete[] array;//Delete old array memory
    return tempGenre;//Updates the pointer of array to instead point to our new array
}

string* resizeDiscographyTrack(string array[], int capacity){//Resize array by creating a new temp array and returning the new arrays pointer value
    string* tempDiscographyTrack = new string[capacity];//New array with new bigger capacity
    delete[] array;//Delete old array memory
    return tempDiscographyTrack;//Updates the pointer of array to instead point to our new array
}

int* resizeDiscographyTrackYear(int array[], int capacity){//Resize array by creating a new temp array and returning the new arrays pointer value
    int* tempDiscographyTrackYear = new int[capacity];//New array with new bigger capacity  
    delete[] array;//Delete old array memory
    return tempDiscographyTrackYear;//Updates the pointer of array to instead point to our new array
}

int* resizeYearRange(int array[], int capacity){//Resize array by creating a new temp array and returning the new arrays pointer value
    int* tempYearRange = new int[capacity];//New array with new bigger capacity  
    delete[] array;//Delete old array memory
    return tempYearRange;//Updates the pointer of array to instead point to our new array
}

void processData(struct musicCollection artist[], string musicCollectionFile){//Put data from file into every music collection struct variables
    ifstream input;//Open file
    input.open(musicCollectionFile);
    if(!input){//Open Validation
        cout << "Error reading file" << endl;
        system("pause");
        exit(-1);
    }

    int i = 0;//Artist Counter
    string temp = "";
    while(!input.eof()){//Write data until the end of file - We use getline in case of spaces - Cannot mix cin with getline (Atleast with ease)
        getline(input, artist[i].name);//Read and save name from file to struct[at current artist]

        getline(input, temp);//Read and save number of genres from file, into a temp string
        artist[i].genreNum = stoi(temp);//Save temp string into genre num by casting temp to int

        artist[i].genre = resizeGenre(artist[i].genre, artist[i].genreNum);//Resize genre array to the inputted number of genres
        for(int k = 0; k < artist[i].genreNum; k++){//Loop for the number of genres inputted
            getline(input, artist[i].genre[k]);//Fill genre array - Pointer to temp array with correct size
        }

        getline(input, temp);//Get starting year
        artist[i].yearStart = stoi(temp);
        getline(input, temp);//Get ending year
        artist[i].yearEnd = stoi(temp);

        artist[i].yearRange = resizeYearRange(artist[i].yearRange, (artist[i].yearEnd - artist[i].yearStart));//Resize year range - The capacity is the range from start year to end year
        for(int k = 0; k < artist[i].yearEnd - artist[i].yearStart; k++){//Loop through number of years, adding years to the range
            if(k == 0){//For the first loop, set year range to year start
                artist[i].yearRange[k] = artist[i].yearStart;
            }
            else{//After the first year, set year to the first year + loop counter
                artist[i].yearRange[k] = (artist[i].yearStart + k);
            }
        }

        getline(input, temp);//Get number of songs
        artist[i].discographyNum = stoi(temp);

        artist[i].discographyTrack = resizeDiscographyTrack(artist[i].discographyTrack, artist[i].discographyNum);//Resize track array
        artist[i].discographyTrackYear = resizeDiscographyTrackYear(artist[i].discographyTrackYear, artist[i].discographyNum);//Resize track year
        for(int k = 0; k < artist[i].discographyNum; k++){//Loop through using number of tracks and save each track title and track year
            getline(input, artist[i].discographyTrack[k], '\t');//Get track name - delimiter of tab

            getline(input, temp);//Get parallel track year as temp and convert to int for track year
            artist[i].discographyTrackYear[k] = stoi(temp);
        }
        i++;//Increment artist number
    }
    input.close();
}

void displayMusicCollection(struct musicCollection artist[]){//Display each music object and its variables
    for(int i = 0; i < artist[0].capacity; i++){//Loop through all artist arrays, artist at i is current object
        if(i > 0){//After the first artist, line break for UX
            cout << "\n";
        }
        cout << "----------------------------------------------" << endl
             << "Artist: " << artist[i].name << endl
             << "Career Range: " << artist[i].yearStart << " - " << artist[i].yearEnd << endl
             << "Genres: ";
        for(int k = 0; k < artist[i].genreNum; k++){//Loop through genres and display each, using genre number
            cout << artist[i].genre[k]
                 << ", ";
        }
        cout << left << setw(100) << "\nDiscography:" << endl
             << left << setw(100) << "Song Title" << left << "Release Year" << endl;
        for(int k = 0; k < artist[i].discographyNum; k++){//Loop through all tracks with discography number and display each track and year released
            cout << left << setw(100) << artist[i].discographyTrack[k]
                 << left << artist[i].discographyTrackYear[k] << endl;
        }
    }
}

void searchName(struct musicCollection artist[]){//Search all artist names and display all struct information for that artist
    string searchTerm = "";
    cout << "Input the artist you would like to find. Case Sensitive" << endl;//Get search term from user
    getline(cin, searchTerm);

    bool marker = false;//Bool marker to pop if search was found
    for(int i = 0; i < artist[0].capacity; i++){//Loop through capacity of artists
        if(artist[i].name == searchTerm){//If search term found display & set found marker 
            marker = true;//Trigger found marker
            cout << "----------------------------------------------" << endl
                 << "Artist: " << artist[i].name << endl
                 << "Career Range: " << artist[i].yearStart << " - " << artist[i].yearEnd << endl
                 << "Genres: ";
            for(int k = 0; k < artist[i].genreNum; k++){//Loop through genres and display each, using genre number
                cout << artist[i].genre[k]
                     << ", ";
            }
            cout << left << setw(100) << "\nDiscography: \n" << endl
                 << left << setw(100) << "Song Title" << left << "Release Year" << endl;
            for(int k = 0; k < artist[i].discographyNum; k++){//Loop through all tracks with discography number and display each track and year released
                cout << left << setw(100) << artist[i].discographyTrack[k]
                     << left << artist[i].discographyTrackYear[k] << endl;
            }
        }
    }
    if(!marker){//If search not found, display error
        cout << "Name not found" << endl;
    }
}

void searchGenre(struct musicCollection artist[]){//Search all artist genres and display each artist and their other genres
    string searchTerm = "";
    cout << "Input the genre you would like to find" << endl;//Get search term from user
    getline(cin, searchTerm);

    bool marker = false;//Bool marker to pop if search was found
    for(int i = 0; i < artist[0].capacity; i++){//Loop through capacity of artists
        if(artist[i].genre[i] == searchTerm){//If search term found display & set found marker 
            marker = true;//Trigger found marker
            cout << "----------------------------------------------" << endl
                 << "Artist: " << artist[i].name << endl
                 << "Career Range: " << artist[i].yearStart << " - " << artist[i].yearEnd << endl
                 << "Genres: ";
            for(int k = 0; k < artist[i].genreNum; k++){//Loop through genres and display each, using genre number
                cout << artist[i].genre[k]
                     << ", ";
            }
        }
    }
    if(!marker){//If not found, display error message
        cout << "Genre not found" << endl;
    }
}

void searchTitle(struct musicCollection artist[]){//Search all artist track titles and display each artist and their other genres
    string searchTerm = "";
    cout << "Input the track title you would like to find. Include quotes surrounding your song. Case sensitive" << endl;//Get user search term
    getline(cin, searchTerm);

    bool marker = false;//Bool marker to pop if search was found
    for(int i = 0; i < artist[0].capacity; i++){//Loop through capacity of artists
        for(int k = 0; k < artist[i].discographyNum; k++){//Loop through number of tracks
            if(artist[i].discographyTrack[k] == searchTerm){//If search term found display & set found marker
                marker = true;//Trigger found marker
                cout << "Artist: " << artist[i].name
                     << " Track: " << artist[i].discographyTrack[k]
                     << " Release Year: " << artist[i].discographyTrackYear[k] << endl;
            }
        }
    }
    if(!marker){//If not found display error
        cout << "Track not found" << endl;
    }
}

void searchYear(struct musicCollection artist[]){//Search all artists active years and display artists active in that year
    string temp = "";
    int searchTerm = 0;
    cout << "Input the year you would like to find artists active in" << endl;//Get user search term
    getline(cin, temp);
    searchTerm = stoi(temp);

    while(searchTerm <= 0){//Input Validation - <=0
        cout << "Choice cannot be less than 0. Re-Enter Input" << endl;
        getline(cin, temp);
        searchTerm = stoi(temp);
    }

    bool marker = false;//Bool marker to pop if search was found
    for(int i = 0; i < artist[0].capacity; i++){//Loop through capacity of artists
        for(int k = 0; k < artist[i].yearEnd - artist[i].yearStart; k++){//Loop through artist active years (Using the year range)
            if(artist[i].yearRange[k] == searchTerm){//If search term found display & set found marker
                marker = true;//Trigger found marker
                cout << "Artist: " << artist[i].name << endl;
            }
        }
    }
    if(!marker){//If not found display error
        cout << "Year not found" << endl;
    }
}

int displayMenu(){//Display menu options in table and return menu choice
    int menuChoice = 0;
    string temp = "";//Temp to hold getline for conversion
    cout << "---------------------------" << endl
         << "           Menu" << endl
         << "---------------------------" << endl
         << "1. Display All Information" << endl
         << "2. Search By Artist Name" << endl
         << "3. Search By Genre" << endl
         << "4. Search By Song Title" << endl
         << "5. Search By Active Year" << endl
         << "6. Exit" << endl
         << "---------------------------" << endl;
    getline(cin, temp);
    menuChoice = stoi(temp);//Convert temp to int for menu choice

    while((menuChoice <= 0) || (menuChoice > 6)){//Input Validation - <= 0 + > 6 
        cout << "Choice cannot be less than 0 or greater than menu size. Re-Enter Input" << endl;
        getline(cin, temp);
        menuChoice = stoi(temp);
    }
    return menuChoice;
}

void processMenu(struct musicCollection artist[], bool &sentinel, int menuChoice){//Process menu input
    switch(menuChoice){//Switch for menu choice to decide which function to call
        case 1:{//Display all
            displayMusicCollection(artist);
            break;
        }
        case 2:{//Search by name
            searchName(artist);
            break;
        }
        case 3:{//Search by genre
            searchGenre(artist);
            break;
        }
        case 4:{//Search by title
            searchTitle(artist);
            break;
        }
        case 5:{//Search by year
            searchYear(artist);
            break;
        }
        case 6:{//Exit 
            sentinel = false;//Set sentinel to false to exit menu loop
            cout << "Exit: Thanks For Playing!" << endl;//Exit message
            break;
        }
        default:{
            cout << "Switch Error" << endl;
        }
    }
}

void deleteArrays(struct musicCollection artist[]){//Delete all dynamically allocated arrays
    for(int i = 0; i < artist[0].capacity; i++){//Loop through array capacity and delete array memories
        delete[] artist[i].genre;
        delete[] artist[i].discographyTrack;
        delete[] artist[i].discographyTrackYear;
        delete[] artist[i].yearRange;
    }
    delete[] artist;
}

int main()
{
    const int capacity = 3;//Capacity for artist arrays
    musicCollection* artist = new musicCollection[capacity];//Dynamic pointer array of structs - Struct array 
    artist->capacity = capacity;//Set all struct artists capacity to the capacity

    string musicCollectionFile = R"(C:\Users\Cortes\CLionProjects\MusicCollectionCRUD\MusicCollection.txt)";
    processData(artist, musicCollectionFile);//Process data from text file into artist structs

    bool sentinel = true;//Sentinel controller 
    int menuChoice = 0;//Menu choice
    while(sentinel){//Sentinel controlled loop
        menuChoice = displayMenu();//Display menu and return choice
        processMenu(artist, sentinel, menuChoice);//Process menu and allow for sentinel exit
    }

    deleteArrays(artist);//Delete all dynamically allocated pointer arrays
    return 0;
}
/*
    Declare struct to hold music collection - Artist name, start/end year, year range, genre number, genres, discography number, track title, track year
        Year range, genres, track title, track year - Dynamic arrays
    Declare capacity for the artist arrays
    Declare array of pointers to structs - Music collection
    Process data:
        Getline each line to get data and save it to artist[counter] and its data type - For each dynamic array, resize w/ the number given as capacity, delete old array
            Genre: Use genre num as the array element location and loop for genre num amount
            Year Range: To resize send (end year - start year) as capacity - Loop through capacity and add year + loop to the next year range (For the first year just assign it to start)
            Discography: Getline with tab as a delimiter between track title and year
        Increment counter to loop through each artist
    Sentinel controlled Search menu:
        Can search by artist name, genre, track title, active year
            Get search term from user and loop through artists w/ capacity, set marker to found if found, if not display error
                Name: Display all object info
                Genre: Display artist and genres
                Track Title: Display Artist and genres
                Year Range: Display artists
    Display All:
        Loop through all variables in a pretty way using setw
    Delete All:
        Delete all dynamically allocated arrays
            Genre, Tracks, Track years, Year Range, Artist
*/