# Uebung_012m_AIS: String Input und Speichern NVS mit Subapp (AIS Adapter)



* * * * * * * * * *

## Einleitung

Diese Übung demonstriert die Verwendung eines **AIS-Adapters** (Application Interface Service) zum Einlesen und Speichern eines Strings im **nichtflüchtigen Speicher (NVS)**. Der Funktionsbaustein `NVS_IN_AND_STORE_AIS` wird als SubApp eingesetzt, um einen vorgegebenen Schlüssel (`KEY`) und eine Objekt-ID (`u16ObjId`) zu parametrieren und so einen beliebigen Stringwert persistent zu speichern.

Die Übung zeigt, wie externe Konstanten aus dem Projektimport genutzt werden können, um die Konfiguration sauber zu halten.

## Verwendete Funktionsbausteine (FBs)

Die Übung enthält einen einzigen SubApp-Baustein, der die gesamte Funktionalität kapselt.

### Sub-Bausteine: `Uebung_012m_sub_AIS`

- **Typ**: `MyLib::sys::NVS_IN_AND_STORE_AIS`
- **Verwendete interne FBs**: Keine (der FB ist als vordefinierter Typ aus einer Bibliothek eingebunden)
- **Parameter**:
  - `KEY` = `KEY_I1_STORE` (Import aus `Uebungen::const::NVS::NVS_Keys::KEY_I1_STORE`)
  - `u16ObjId` = `InputString_S1` (Import aus `Uebungen::const::UT::DefaultPool::InputString_S1`)
- **Funktionsweise**:
  Der FB `NVS_IN_AND_STORE_AIS` wartet auf einen eingehenden String über den AIS-Adapter. Sobald ein gültiger Wert ankommt, wird dieser unter dem angegebenen NVS-Schlüssel (`KEY`) dauerhaft gespeichert. Die Objekt-ID (`u16ObjId`) identifiziert die Datenquelle oder den Speicherort im DefaultPool. Das Zusammenspiel von AIS und NVS ermöglicht eine hardwarenahe, asynchrone Datenübernahme, ohne dass zyklische Abfragen nötig sind.

## Programmablauf und Verbindungen

Die SubApp besitzt keine eigenen Ein‑/Ausgangsschnittstellen (InterfaceList ist leer). Sie wird als eigenständige Komponente in eine übergeordnete Applikation eingebettet. Die Verbindung zur Außenwelt erfolgt ausschließlich über den AIS-Adapter, der von der Laufzeitumgebung bereitgestellt wird.

- Die Konstanten `KEY_I1_STORE` und `InputString_S1` müssen im Projekt als Konstanten definiert sein und werden beim Import in die SubApp übernommen.
- Die Ausführung startet, sobald der AIS-Adapter einen neuen String liefert. Der FB speichert diesen Wert dann persistent.

**Lernziele**:
- Verständnis des AIS-Adapter-Konzepts für asynchrone Datenaufnahme
- Persistente Speicherung von Stringdaten im NVS
- Einsatz von importierten Konstanten zur Parametrierung von Funktionsbausteinen

**Schwierigkeitsgrad**: Fortgeschritten  
**Vorkenntnisse**: Grundlagen der 4diac-IDE, NVS-Konzept, Umgang mit Konstanten und Importen

## Zusammenfassung

Die Übung `Uebung_012m_AIS` zeigt, wie ein String über einen AIS-Adapter eingelesen und mittels eines vordefinierten Bausteins sicher im nichtflüchtigen Speicher abgelegt wird. Durch die strikte Trennung von Konstanten und Logik bleibt die Konfiguration flexibel und wiederverwendbar.