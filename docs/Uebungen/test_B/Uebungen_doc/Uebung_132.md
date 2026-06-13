# Uebung_132: Übung zu ISOBUS Request Message




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_132`.

----


## Übersicht

[cite_start]In dieser Übung wird der Baustein `AlPgnRxNew8B_REQ` verwendet[cite: 1].

![Uebung_132_network](./Uebung_132_network.svg)

Anstatt passiv auf eine Nachricht zu warten, kann die Steuerung hier aktiv eine Anfrage (Request) nach einer bestimmten PGN an den Partner senden. Ein Klick auf Taster **I1** löst das `REQ`-Ereignis aus, woraufhin die Steuerung die entsprechende Anforderungs-Nachricht auf den Bus schickt. Sobald der Partner antwortet, wird dies als regulärer Empfang (`IND`) gewertet und verarbeitet.