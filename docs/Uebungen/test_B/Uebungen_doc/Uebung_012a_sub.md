# Uebung_012a_sub: Numeric Value Input und Speichern NVS mit Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

## Übersicht

[cite_start]Dieser Baustein dient als universelle Schnittstelle für Benutzereingaben, die dauerhaft im NVS (Non Volatile Storage) gespeichert werden sollen[cite: 1].
Er bündelt folgende Funktionen:

![Uebung_012a_sub_network](./Uebung_012a_sub_network.svg)

1.  **Eingabe**: Einlesen eines Werts vom Terminal (`NumericValue_ID`).
2.  **Speichern**: Automatisches Ablegen im Flash-Speicher unter einem wählbaren Schlüssel (`KEY`).
3.  **Laden**: Automatisches Auslesen des Werts beim Systemstart (`INITO -> GET`).
4.  **Rückmeldung**: Senden des (geladenen oder geänderten) Werts an die Anzeige am Terminal.
Zusätzlich bietet der Baustein einen Eingang `REQ`, um den Anzeige-Refresh extern (z.B. bei Terminal-Neuverbindung) anzustoßen.



## 🛠️ Zugehörige Übungen

* [Uebung_012a](Uebung_012a.md)

