# Uebung_012c: Numeric Value Input und Speichern INI mit Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_012c`. Hier wird demonstriert, dass auch Text-Informationen persistent gespeichert werden können.

----


## Ziel der Übung

Umgang mit dem Datentyp `STRING` bei der Speicherung.

-----

## Beschreibung und Komponenten

[cite_start]In `Uebung_012c.SUB` wird ein String-Wert über einen INI-Baustein verwaltet[cite: 1].

### Funktionsbausteine (FBs)

  * **`INI`**: Hier konfiguriert für den Datentyp `STRING`.
  * **`Q_StringValue`**: Ein ISOBUS-Ausgangsbaustein, der speziell für die Anzeige von Texten (anstelle von Zahlen) gedacht ist.

-----

## Funktionsweise

Der Ablauf ist identisch zur numerischen Speicherung, jedoch fließen über die Datenverbindungen nun Zeichenketten. Beim Systemstart wird der gespeicherte Text (z.B. ein Gerätename oder ein Benutzerprofil) geladen und an das Terminal gesendet.

-----

## Anwendungsbeispiel

**Personalisierung**:
Der Nutzer kann am Terminal seinen Namen oder den Namen des Feldes eingeben, auf dem er gerade arbeitet. Diese Information wird dauerhaft gespeichert und kann später für Protokollierungszwecke (z.B. Task Controller) genutzt werden.