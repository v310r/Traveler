For this project, a https://github.com/v310r/Knight project was taken as a reference but upgraded (a lot), and basically, a whole new game was created.

git clone --recursive https://github.com/v310r/Traveler.git OR git clone --recurse-submodules https://github.com/v310r/Traveler.git to clone the repo

This project only supports Windows. To support other platforms build settings should be tuned.

To build the project, you should first build the SFML library. Run cmake in the build folder as it is shown in the picture below:

![image](https://github.com/v310r/Traveler/assets/80487632/7930e5e7-408d-4167-a98e-0daff2a6ff21)


Then, go to the root folder and run GenerateProject.bat. Open a solution, choose whatever configuration you'd prefer (Debug or Release), and build the whole solution.

Now you should be able to play the game, enjoy :-).
