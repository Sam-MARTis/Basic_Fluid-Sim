# Docs
Honestly, this is more for me to keep track of what the hell I was even thinking while I made the functions so I can take breaks and not be completely lost when I come back.



### Display functions
1. The end sim should have options of displaying the pressure, divergence, etc of the cells.
2. It should also have an option of borders between cells, atleast for debugging. I'll set thickness to zero later.
3. It should be able to render the wall velocities, so `hvels` and `vvels` so that they are attached to the cell.
4. It should also be able to render a flow field so I can see verify that interpolation is working.
5. It should be able to render moving particles like smoke or some beads. 


5 we can work on once the sim works. 
For 1, I am planning to have a `display_shapes` function that takes in the sfml shapes and a pointer to the property that needs to be displayed. 
Since different properties need different normalization factors, I will pass in a property range as well. 
```
display_shapes(rendering_window, shapes, dimensions, properties_array, property_min, property_max)
```


The GUI has a dropdown menu for choosing values like pressure, divergence, constant colour, etc.
The property choosen is then used in the main.cpp to choose the appropriate property of the fluid sim container structure that contains all the data. This chosen property (an array pointer) is passed into the `display_shapes` function

