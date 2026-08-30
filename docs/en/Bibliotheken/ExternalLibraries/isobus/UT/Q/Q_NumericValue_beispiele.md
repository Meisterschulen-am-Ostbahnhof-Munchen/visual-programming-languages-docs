### Q\_NumericValue

![Q_NumericValue function block overview](https://user-images.githubusercontent.com/113907471/204326982-47eea33a-9b9c-4107-8f96-97c85a945fbc.png)
Normative Reference:
This function block refers to section ISO 11783-6 F.22 Change Numeric Value command
CAUTION: This command can be called as often as desired by the application programmer; however, excessively frequent calls can severely overload the ISOBUS, therefore this function block should be used with caution.

The purpose of this function block is to update one of the following objects displayed on a VT:

- Boolean input field: 1 byte for TRUE/FALSE

![Boolean input field representation on VT](https://user-images.githubusercontent.com/69573151/227978868-275bbdb4-4a27-4325-b79a-e06a92a48244.png)

- Number input field: 4 bytes for integer input

![Numeric input field on Virtual Terminal](https://user-images.githubusercontent.com/69573151/227978954-813af40a-0d6b-4add-92ee-4adb9e6a1df9.png)

- List input field: 1 byte for list index

![List input field VT object](https://user-images.githubusercontent.com/69573151/227979018-91510384-180d-450b-a34e-c8a8ec7c12ed.png)

- List output field: 1 byte for list index
- (same as list input field, but not present in VT3)
- Number output field: 4 bytes for integer output

![Numeric output field on VT](https://user-images.githubusercontent.com/69573151/227979612-e3538226-b587-42c3-b123-4790dce151f0.png)

- Meter: 2 bytes for integer value

![Gauge meter display object](https://user-images.githubusercontent.com/69573151/227979569-f4270f16-58ba-442a-9833-7a794b6c9237.png)

- Linear bar graph: 2 bytes for integer value

![Linear bar graph object on VT](https://user-images.githubusercontent.com/69573151/227979543-375aee21-c7d6-4151-b027-16073846f320.png)

- Arched bar graph: 2 bytes for integer value

![Arched bar graph object](https://user-images.githubusercontent.com/69573151/227979499-dd27d3ff-2bd5-40ab-b204-89dd96728006.png)

- Number variable: 4 bytes for integer value
- The Number variable cannot be displayed directly on the screen, but it can be linked to all previously mentioned objects; advantage: multiple links are possible.
- Object pointer: 2 bytes for Object ID
- Useful for showing and hiding other objects instead of the pointer.

![Object pointer configuration](https://user-images.githubusercontent.com/69573151/227979478-da0e0584-7714-442f-a5ba-ffce7d5b882b.png)

Cross-references:

EXAMPLE

Counter with reset

![Circuit example counter with reset](https://user-images.githubusercontent.com/113907471/204327132-b1a058c2-7ccb-4374-af56-d309ae8798a5.png)
