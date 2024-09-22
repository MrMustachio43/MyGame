This is a game i made for my 6th form programming prodject in c++. Whilst it's a bit broken, here are the features i successfully coded in:

- **Procedural level generation** using **cellular automata** and dynamic arrays
- **Saving Levels**, including the characters position
- **Loading Levels** with the character in the correct location
- Character **movement system** (8 DOF, attack animation in up down left right)
- Working **collision** between character and surroundings
- Menu system (not fully implimented, but the building blocks were there)

The character it self made use of a class sytem with get and set methods that i called to find out the locations, when to walk/attack, and would have easily expanded into a working health system for the character too.

Some examples of the proccedural generation:
![Screenshot 2023-04-24 123339](https://github.com/user-attachments/assets/328bef44-23ff-44c4-9e37-6c30132b6f01)

![Screenshot 2023-04-24 105302](https://github.com/user-attachments/assets/ad4ec267-1b37-4e68-9e68-5ff66a0d0863)

Bellow is behind the scenes of whats happening for the when a map has generated:

First, we generated noise:
![Screenshot 2023-04-24 105453](https://github.com/user-attachments/assets/84180734-d509-47c0-a405-e1357068e846)

Then we smooth it out:
![Screenshot 2023-04-24 105547](https://github.com/user-attachments/assets/dc2dce9d-697d-497c-9bee-1871aa848380)

Then i find the edges and assign it a number (through an enum) depending on what piece it should be e.g. 4 = corner wall, -4 = the same wall but flipped on the y axis
![Screenshot 2023-04-24 105610](https://github.com/user-attachments/assets/ee140d4c-2d3b-4197-9fac-04b96da7217e)

Then, using a map of available spaces, we plant trees. 2 is the base of the tree (and where we want to collide) and 9 is the part we would like to appear under and determine if the tree should be transparent
![Screenshot 2023-04-24 105728](https://github.com/user-attachments/assets/7baa95bf-681b-44a2-87b7-6ae48443646b)
![Screenshot 2023-04-21 190150](https://github.com/user-attachments/assets/820e1b89-3b53-49a2-b77a-c5be3d908aab)

