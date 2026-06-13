# Uebung_012k_AIS: String Input und Speichern INI mit Subapp (AIS Adapter)



* * * * * * * * * *
## Einleitung
Die Übung *Uebung_012k_AIS* demonstriert, wie ein eingegebener String (z. B. Benutzereingabe oder Sensorwert) in einem nichtflüchtigen Speicher (NVS) abgelegt wird. Der Zugriff erfolgt über einen AIS-Adapter (Application Interface Subapp), der die Kommunikation mit der Speicherlogik vereinfacht. Ziel ist es, den Umgang mit persistenten Daten und Adapter-basierten Subapplikationen in der 4diac-IDE zu erlernen.

## Verwendete Funktionsbausteine (FBs)
Die Übung besteht aus einer einzigen Subapplikation, die alle notwendigen Funktionen kapselt.

### Sub-Baustein: Uebung_012k_sub_AIS
- **Typ**: `MyLib::sys::INI_IN_AND_STORE_AIS`
- **Verwendete interne FBs**: nicht einsehbar (intern durch den Typ definiert)
- **Parameter**:
  - `KEY` = `KEY_I1_STORE` (Konstante aus `Uebungen::const::NVS::NVS_Keys`)
  - `SECTION` = `SECTION_I1_STORE` (Konstante aus `Uebungen::const::NVS::NVS_Keys`)
  - `u16ObjId` = `InputString_S1` (Konstante aus `Uebungen::const::UT::DefaultPool`)
- **Funktionsweise**:  
  Dieser Sub-Baustein empfängt über einen AIS-Adapter einen String-Eingangswert. Beim Eintreffen eines entsprechenden Ereignisses (vermutlich vom Adapter) wird der Wert unter der angegebenen Section und dem Key im NVS gespeichert. Die Objekt-ID (`u16ObjId`) identifiziert dabei den konkreten Eingangskanal. Nach erfolgreichem Speichern wird ein Bestätigungssignal (z. B. `INIT` oder `CNF`) zurückgegeben.

## Programmablauf und Verbindungen
1. **Initialisierung**: Die Subapp `Uebung_012k_sub_AIS` wird mit den vordefinierten Konstanten parametriert.  
2. **Datenfluss**: Ein String wird über den AIS-Adapter an den Sub-Baustein übergeben.  
3. **Speicherung**: Der Sub-Baustein speichert den String persistent in der INI‑ähnlichen NVS-Struktur unter der Section `SECTION_I1_STORE` und dem Schlüssel `KEY_I1_STORE`.  
4. **Rückmeldung**: Nach Abschluss der Speicherung wird ein Ereignis ausgelöst (z. B. `CNF`), das den erfolgreichen Abschluss signalisiert.

Die Übung enthält keine weiteren Verbindungen oder Ereignisverknüpfungen – die gesamte Logik ist im Typ `INI_IN_AND_STORE_AIS` gekapselt. Dadurch wird eine klare Trennung zwischen Applikationslogik und Speicherzugriff erreicht und die Wiederverwendbarkeit erhöht.

## Zusammenfassung
*Uebung_012k_AIS* zeigt, wie man einen sicheren, persistenten Speichervorgang für einen String mithilfe eines AIS-Adapters realisiert. Der Lernende erhält Einblicke in:
- die Verwendung von NVS-Konstanten (`KEY`, `SECTION`),
- die Einbindung eines Adapter-basierten Subbausteins,
- die Parameterübergabe über die 4diac-IDE.

Nach Abschluss der Übung kann der Entwickler dieses Muster auf eigene Anwendungen übertragen, bei denen Benutzereingaben oder Konfigurationsdaten dauerhaft gespeichert werden müssen.