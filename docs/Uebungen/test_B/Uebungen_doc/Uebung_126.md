# Uebung_126: Übung zu ISOBUS Send Message Cyclic (mit CB)




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_126`.

----


## Übersicht

[cite_start]Verwendung des Bausteins `AlPgnTxNew8Bcycl_REQ`[cite: 1].
Hier wird die Nachricht in einem festen Zeitintervall (Parameter `u16DefRepRate = 500`ms) wiederholt auf den Bus gesendet. Der Baustein nutzt ebenfalls den Callback-Mechanismus (`CB`), um vor jedem Sendevorgang die allerneuesten Daten aus der Applikation abzufragen. Dies ist das Standard-Verfahren für Status-Nachrichten, die permanent zur Verfügung stehen müssen (z.B. Herzschlag oder Sensordaten).

![Uebung_126_network](./Uebung_126_network.svg)
