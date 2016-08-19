#User Documentation

**Overview**

The program handles RBML – Recipe Book Markup Language – files, in order to read, store and manipulate recipes. RBML files may have two major formats – Cookbook and Inventory (See File format section for more information on file types). Once these files are loaded into the program, the recipes can be added into a Menu that will handle operation on selected recipes. Additionally, the Menu can be used to compare the combined equipment and ingredient lists of the recipes contained, with the inventory to determine a shopping list of required materials, along with the amount deficient.

**File format**

There are two types of files, as previously stated in the overview section of this documents. Each file has unique properties that allows it to be correctly processed by the program.
- Cookbook: This may or may not be an actual cookbook file, but rather the broadest scale to which the program can parse and understand it. Generally, a cookbook may contain a title, sections and recipes. Each section may have multiple recipes contained in them. Although many features of a recipe and its parent containers (sections and cookbooks) are understood by the program, there may be features that are not well understood. When such features are detected, the program will notify you which feature it didn’t understand, but will process the rest of the file normally -- for a list of supported features, see the supported features section at the end of this document. Similarly, for a recipe file to be processed, not all information has to be there. But, a recipe must at a minimum include a title and logically, an ingredient list and preparation. If a recipe has no title, the program will read the recipe file in, but you will not have any access to the recipe as the title is the means by which a recipe is called from within the program.
- Inventory: This file should only contain a list of ingredients and equipments. Unlike a recipe/cookbook file, an Inventory file does not need to have a title, nor would it be understood by the program if it had one. The list of ingredients should be sectioned under ingredientlist, and the list of equipment under equipmentlist. If there is more than one equipment, it should be listed as separate equipment for the amount there is. Although the formatting requires that an equipment be listed as many times as it’s quantity, the program will automatically determine the quantity of the equipment when reading the inventory file. For example, if an equipment “spoon” is listed 5 times in an inventory file, when the program reads it, it stores it as one equipment but automatically assigns it a quantity of 5, which can then be operated on by increasing or decreasing the quantity. Handling quantity using \<quantity\> tag might be included for equipments in the future.

**Commands**

**Command Line Arguments:**

1. -s : The program will start in silent mode.
2. -v : The program will start in verbose mode.
3. -i filename: The program will load an inventory file “filename” and add into its current inventory.
4. -r filename : The program will load a recipe file “filename” into its current cookbook.

*Note: If both -s and -v are used, the argument that appears last will determine the mode at program startup. More than one instance of the –i and –r arguments may be used to load multiple inventory and recipe files respectively.*

**Internal Commands:**

*Note: Items displayed as \<item\> indicate a user input field for proving the item name/type/description. The angle brackets should not be used during input.*

**0. Exit:** The program will terminate. In verbose mode, a farewell message will be displayed upon exiting. Note that all data, except those saved to file, will be lost upon exit.

**1. Input recipe \<file\>:** A recipe file of name “file” will be loaded into a generic cookbook that contains a list of recipes. If the recipe file contains a cookbook, the cookbook in the recipe file will replace the existing cookbook. Additional input of recipe files containing cookbooks will not replace the existing cookbook, but rather merge the two. If there are any formatting errors or unknown tags present, it will be displayed in the console.

**2. Input inventory \<file\>:** An inventory file of name “file” will be loaded into the program’s inventory. When loading multiple files, it the files contain items that are already in the program’s inventory, they will be added to these items. If not, a new instance is created. For ingredients with different units, if both units are supported (see supported features section), then the ingredients are added and the unit is automatically converted to the best fit – adding 1 tbsp to 1 gallon will not result in the quantity being displayed as 257 tbsp due to impracticality.

**3. Subtract inventory \<file\>:** An inventory of file name “file” will be loaded and its items subtracted from the current inventory. If there is more of an item in the selected file than the inventory, the subtraction will lead to the item being removed from the current inventory but an error will be displayed for an attempt to reduce an item’s quantity to negative.

**4. Add \<recipe name\>:** A recipe with the name “recipe name” will be selected from the cookbook and added to the menu. The program allows addition of one recipe to the menu, (as a recipe with similar name could have different preparations) but will display a warning of possible duplicates. It is up to you, the user, to determine if multiple instances of one recipe is needed on the menu.

5**. Remove \<recipe name\>:** A recipe with the name “recipe name” will be removed from the menu. This will not remove the recipe from the program’s cookbook, though. If there are multiple instances of a recipe, all instances will be removed.

**6. Reset:** All recipes will be removed from the menu.

**7. Output \<file\>:** This will save all recipes in the current menu to a file in the RBML format. All
information of the recipe that was processed during input will be saved. See supported
features section for more information.

**8. Print current menu:** A list of titles of recipes in the menu will be printed, in the order they
were added.

**9. Print \<recipe name\>:** A recipe of title “recipe name” will be printed if it is stored in the
program. This will print all information associated with the recipe, such as ingredients used, preparation steps and additional information about the recipe processed during input.

**10. Increase \<ingredient\> [\<quantity\>[\<unit\>]]:** The ingredient of name “ingredient” in the inventory will be increased by an optional “quantity unit” amount. By default, if no quantity is provided, the ingredient will be increased by 1 quantity. For ingredients with quantities bearing units, it is strongly suggested that the quantity and units be provided. The quantity should be a whole number or a fraction. Additionally, only positive number may be used for the quantity. The ingredient name, quantity (optional) and unit(optional) must be input in the shown sequence.

**11. Reduce \<ingredient\> [\<quantity\> [\<unit\>]]:** Similar format as the increase command, but instead of increasing the ingredient quantity, this decreases the quantity by the specified amount(if any). All rules specified for the increase command apply. In addition, if an ingredient is reduced to a negative number, an error is thrown and the amount is reduced at 0. Ingredients reduced to 0 will be removed from the inventory.

**12. Insert \<equipment\>:** An equipment of name “equipment” will be inserted in the inventory. If the equipment already exists, it’s quantity will be incremented.

**13. Delete \<equipment\>:** The equipment of name “equipment” will be removed from the inventory. Note: even if the equipment has a quantity of more than 1, they will all be removed.

**14. Print ingredient inventory:** A list of all ingredients in the inventory will be printed in the format \<quantity\> \<unit\> \<ingredient\> -- an ingredient per line.

**15. Print equipment inventory:** A list of all equipment in the inventory will be printed. If there is more than 1 amount of an equipment, the amount will be printed along the equipment. Otherwise, no amount will be printed. For example, if there are 20 forks and a knife in the inventory, the output would look like: 
```
  20 fork
  knife
```

**16. Print ingredient list:** A list of the combined ingredients of all recipes in the menu will be printed. The format for printing inventory ingredients will be followed.

**17. Print ingredient shopping list:** This will print the difference of the inventory ingredients from the ingredients list.

**18. Output ingredients shopping list \<file\>:** This will save the shopping list of ingredients to a file in RBML format.

**19. Print equipment list:** A list of the combined equipments of all recipes in the menu will be printed. The format for printing inventory equipments will be followed.

**20. print equipment shopping list:** This will print the difference of the inventory equipments from the equipments list.

**21. Output equipment shopping list \<file\>:** This will save the shopping list of equipments to a file in RBML format.

**22. Help:** Print a description of the supported commands to the console.

*Restrictions on command use: All commands that take in a recipe, ingredient or equipment name from user input will not work with other commands if used in the same line. For example, trying to add and delete a recipe by using 4 recipe name 5 another recipe will result in an error. Use such commands one at a time.*

**Supported Features:**

Items in **bold** are the actual recipe content. Everything else is listed as tag format nested accordingly. Note: Tags are only defined once. If they appear multiple times, subsequent tags will not be redefined.
- cookbook (title?, (section | recipe)+)
  - section (title, recipe+)
    - recipe (title, recipeinfo, ingredientlist, preparation, serving, notes)
      - title (**text**)
      - recipeinfo (author | blurb | effort | genre | preptime | source | yield)
        - author (**text**)
        - blurb (**text**)
        - effort (**text**)
        - genre (text)
        - preptime (**text**)
        - source (**text**)
        - yield (**text**) 
      - ingredientlist (ingredient)
        - ingredient (**text** | quantity | unit | fooditem)
        - fooditem (**text**)
        - quantity (**integer / fraction**) 
        - unit (**text**)
      - preparation (**text** | equipment | step | timedstep)
        - equipment (**text**)
        - timedstep (**text**, step, steptime)
          - steptime (**text**, (timeamt, timeunit, timetype)+)
            - timeamt (**text**)
            - timeunit(**text**)
            - timetype (**text**)
        - step (**text** | equipment ) 
      - serving (**text**)
      - notes (**text**)
- inventory (ingredientlist | equipmentlist)+
  - equipmentlist (equipment)
