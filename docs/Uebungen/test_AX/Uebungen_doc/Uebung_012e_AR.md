# Uebung_012e_AR: Numeric Value Input PHYS und Speichern INI mit Subapp (AR Adapter)



* * * * * * * * * *

## Einleitung

Diese Übung demonstriert die Eingabe eines numerischen Werts (PHYS) und dessen Speicherung mittels eines SubApp, der einen AR-Adapter verwendet. Der eingegebene Wert wird unter einem vordefinierten Schlüssel in einem nichtflüchtigen Speicher (NVS) abgelegt. Die Übung zeigt, wie Konstanten aus einem zentralen Pool (`DefaultPool_Numeric`) sowie NVS-Schlüssel importiert und in einem SubApp-Parameter genutzt werden.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: Uebung_012e_sub_AR

- **Typ**: `MyLib::sys::INI_IN_AND_STORE_AR`
- **Verwendete interne FBs**: Keine weiteren FBs im Netzwerk – der SubApp kapselt die gesamte Logik zur Initialisierung und Speicherung.
- **Parameter**:
  - `KEY` = `KEY_I1_STORE` (Konstante aus `Uebungen::const::NVS::NVS_Keys`)
  - `SECTION` = `SECTION_I1_STORE` (Konstante aus `Uebungen::const::NVS::NVS_Keys`)
  - `stObj` = `InputNumber_I1` (Konstante aus `Uebungen::const::UT::DefaultPool_Numeric`)
- **Funktionsweise**:  
  Der SubApp `INI_IN_AND_STORE_AR` erwartet einen numerischen Eingangswert (z. B. über den AR-Adapter) und speichert diesen im nichtflüchtigen Speicher unter dem angegebenen Abschnitt und Schlüssel. Die Konstanten `KEY_I1_STORE` und `SECTION_I1_STORE` definieren den genauen Speicherort. Die Konstante `InputNumber_I1` stellt den Initialwert oder die Struktur des zu speichernden Objekts bereit.

## Programmablauf und Verbindungen

- **Lernziele**:
  - Anwendung von AR-Adaptern in SubApps
  - Umgang mit NVS-Konstanten und Konstanten-Pools
  - Parametrisierung von SubApps zur Konfiguration von Speicherorten
- **Schwierigkeitsgrad**: Mittel
- **Vorkenntnisse**: Grundlagen der 4diac-IDE, Erstellung von SubApps, Verständnis von AR-Schnittstellen und nichtflüchtigen Speichern.

Die Übung besteht aus einem einzigen SubApp, der in ein übergeordnetes System eingebunden wird. Der SubApp wird mit den drei Parametern konfiguriert. Die Verbindung des AR-Adapters und die Bereitstellung des numerischen Werts erfolgen außerhalb dieser SubApp-Definition (z. B. in der übergeordneten Applikation). Die gespeicherten Daten können anschließend über die gleichen Schlüssel wieder ausgelesen werden.

## Zusammenfassung

Die Übung `Uebung_012e_AR` zeigt eine kompakte Lösung zur persistierenden Speicherung eines numerischen Wertes unter Verwendung eines SubApp mit AR-Adapter. Durch die Auslagerung der Speicherlogik in den wiederverwendbaren SubApp `INI_IN_AND_STORE_AR` und die zentrale Definition von Schlüsseln und Objekten wird eine klare Trennung von Konfiguration und Funktionslogik erreicht.