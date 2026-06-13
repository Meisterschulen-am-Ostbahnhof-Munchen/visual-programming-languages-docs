# Uebung_012f_AR: Numeric Value Input PHYS und Speichern NVS mit Subapp (AR Adapter)



* * * * * * * * * *

## Einleitung

Diese Übung befasst sich mit dem Einlesen eines numerischen Werts (physikalische Größe) und dessen Speicherung im nichtflüchtigen Speicher (NVS) unter Verwendung eines AR-Adapters. Die SubApp dient als Baustein für Anwendungen, die einen Wert einmalig einlesen und dauerhaft ablegen müssen.

## Verwendete Funktionsbausteine (FBs)

### Sub-Baustein: `Uebung_012f_sub_AR`
- **Typ**: `MyLib::sys::NVS_IN_AND_STORE_AR`
- **Parameter**:
  - `KEY` = `KEY_I1_STORE`
  - `stObj` = `InputNumber_I3`
- **Funktionsweise**:  
  Der Baustein nimmt über den eingebauten AR-Adapter einen numerischen Wert entgegen. Der Datentyp und die Struktur des Werts sind durch die vorgegebene Konstante `InputNumber_I3` aus der Bibliothek `DefaultPool_Numeric` definiert. Der gelesene Wert wird unter dem Speicherschlüssel `KEY_I1_STORE` aus der Konstantenbibliothek `NVS_Keys` im nichtflüchtigen Speicher abgelegt.

## Programmablauf und Verbindungen

Die SubApp `Uebung_012f_AR` selbst besitzt keine eigenen Ein- oder Ausgangsschnittstellen. Sie instanziiert den fertigen Subbaustein `Uebung_012f_sub_AR` und versorgt ihn mit den beiden Parametern `KEY` und `stObj`. Diese Parameter werden aus den importierten Bibliotheken mit den entsprechenden Konstanten belegt. Der Baustein führt dann die gesamte Logik zum Empfang des Werts über den AR-Adapter und zum Speichern im NVS aus.

**Lernziele dieser Übung:**
- Verstehen, wie ein AR-Adapter für die Werteingabe verwendet wird.
- Speichern von Werten im nichtflüchtigen Speicher mit vordefinierten Schlüsseln.
- Verwaltung von Konstanten aus externen Bibliotheken.

**Schwierigkeitsgrad:** Mittel  
**Vorkenntnisse:** Grundlegendes Verständnis von 4diac‑FB‑Netzwerken, SubApps und der Verwendung von Adaptern.

## Zusammenfassung

Die Übung `Uebung_012f_AR` demonstriert das persistente Ablegen eines numerischen Werts mithilfe eines AR-Adapters. Der vorgefertigte Baustein `NVS_IN_AND_STORE_AR` wird parametriert und in einer SubApp gekapselt, wodurch eine klare und wiederverwendbare Lösung für das Einlesen und Speichern von Daten entsteht.