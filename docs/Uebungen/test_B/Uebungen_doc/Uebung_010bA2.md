# Uebung_010bA2: Toggle Flip-Flop mit IE AuxFunction2_X1 AuxEnabled




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_010bA2`. Hier geht es um die Feinheiten der AUX-Spezifikation bezüglich rastender und tastender Eingänge.

----


## Funktionsweise

[cite_start]Verwendet `AuxFunction2_X1` mit dem Event `AuxEnabled`[cite: 1]. Das Verhalten hängt vom Typ des zugewiesenen Bedienelements (Joystick-Taste) ab:

![Uebung_010bA2_network](./Uebung_010bA2_network.svg)

*   Bei einem **tastenden Bediener** (NonLatched) wird das Event nur einmal beim Drücken gesendet.
*   Bei einem **rastenden Bediener** (Latched) wird das Event zyklisch wiederholt, solange der Schalter aktiv ist.
Dies verdeutlicht, wie die Software auf die Hardware-Eigenschaften des verwendeten Joysticks reagiert.