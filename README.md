# C++ CRUD Application - Using Manual Array Sizing & Structs
## Music Collection Create, Read, Update, Delete project that reads in a .txt file of known format and ports data into a struct.

### Users can prefrom all CRUD utilities from console menu.
![image](https://github.com/LuisAlanCortes/MusicCollectionCRUD/assets/110257548/b03e96c3-eac2-496c-832e-7b4d6faab20f)

### Search Functionality
![image](https://github.com/LuisAlanCortes/MusicCollectionCRUD/assets/110257548/b0078bbe-137b-45a9-9bb0-b12ed8bb0212)

## Code Breakdown:
- Declare struct to hold music collection - Artist name, start/end year, year range, genre number, genres, discography number, track title, track year
        - Year range, genres, track title, track year - Dynamic arrays
    - Declare capacity for the artist arrays
    - Declare array of pointers to structs - Music collection
    - Process data:
        - Getline each line to get data and save it to artist[counter] and its data type - For each dynamic array, resize w/ the number given as capacity, delete old array
            - Genre: Use genre num as the array element location and loop for genre num amount
            - Year Range: To resize send (end year - start year) as capacity - Loop through capacity and add year + loop to the next year range (For the first year just assign it to start)
            - Discography: Getline with tab as a delimiter between track title and year
        - Increment counter to loop through each artist
    - Sentinel controlled Search menu:
        - Can search by artist name, genre, track title, active year
            - Get search term from user and loop through artists w/ capacity, set marker to found if found, if not display error
                - Name: Display all object info
                - Genre: Display artist and genres
                - Track Title: Display Artist and genres
                - Year Range: Display artists
    - Display All:
        - Loop through all variables in a pretty way using setw
    - Delete All:
        - Delete all dynamically allocated arrays
            - Genre, Tracks, Track years, Year Range, Artist
