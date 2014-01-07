DwarfEngine
===========

*A C++ SDL Engine Framework*

Dwarf oriented framework for SDL (Simple DirectMedia Library).


- Each entity is a Dwarf. 
- All Dwarves are connected each other within tree relation ship.
- If mother goes somewhere, all descendants of her go with her.
- If mother rendered, all children rendered after her.



####CLASSES:
- **Dwarf:** Drawables' base class.
- **Modifier:** Makes modification over time on Dwarves.
- **Haulier:** Modifier; moves Dwarf to some point. Can queue up the routes and supports *easings* for each route.
