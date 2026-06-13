# Uebung_012a_AX: Numeric Value Input und Speichern (Adapter Version)



* * * * * * * * * *

## Einleitung

Diese Übung vermittelt den Umgang mit Adaptern zur numerischen Werteingabe und deren persistenter Speicherung im nichtflüchtigen Speicher (NVS). Der Funktionsbaustein `Uebung_012a_AX` kapselt die gesamte Logik in einem SubApp, der über einen Adapter einen Zahlenwert empfängt und unter einem definierten Schlüssel speichert. Die Adapter‑Variante ermöglicht eine flexible Anbindung an verschiedene Eingabequellen.

Der Baustein selbst besitzt keine sichtbaren Ein‑/Ausgangsschnittstellen – die Kommunikation erfolgt vollständig über den Adapter und die konfigurierten Konstanten.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: Uebung_012a_sub_AUDI

- **Typ**: `MyLib::sys::NVS_IN_AND_STORE_AUDI`
- **Verwendete interne FBs**:  
  Nicht näher spezifiziert – der Baustein enthält eine gekapselte Implementierung zur Adapter‑basierten Eingabe und NVS-Speicherung.
- **Parameter**:
  - `KEY` = `KEY_I1_STORE`  
    (Schlüssel, unter dem der Wert im NVS abgelegt wird; definiert in `Uebungen::const::NVS::NVS_Keys`)
  - `u16ObjId` = `InputNumber_I1`  
    (Identifikation des Eingabewerts; definiert in `Uebungen::const::UT::DefaultPool`)
- **Funktionsweise**:  
  Der FB liest bei Aktivierung den aktuellen numerischen Wert von einem Adapter ein und speichert diesen persistent im NVS unter dem angegebenen `KEY`. Die Objekt‑ID `InputNumber_I1` referenziert die Bereitstellung des Werts durch die übergeordnete Umgebung (z. B. eine HMI‑Eingabe oder eine übergeordnete Steuerung).

## Programmablauf und Verbindungen

Der SubApp `Uebung_012a_AX` besteht aus einem einzelnen Netzwerk, das den FB `Uebung_012a_sub_AUDI` enthält. Es sind keine weiteren Verbindungen oder Ereignisverkettungen sichtbar, da alle Interaktionen über den Adapter und die parametrierten Konstanten gesteuert werden.

**Ablauf**:
1. Die übergeordnete Applikation aktiviert den SubApp (z. B. durch ein Ereignis).
2. Der FB `Uebung_012a_sub_AUDI` liest den aktuellen Wert vom Adapter ein.
3. Der eingelesene Wert wird unter dem Schlüssel `KEY_I1_STORE` im NVS gespeichert.

**Lernziele**:
- Verständnis der Adapter‑Schnittstelle für Eingabewerte.
- Kennenlernen der persistenten Speicherung mit NVS.
- Umgang mit konstanten Schlüsseln und Objekt‑IDs aus getrennten Const‑Quellen.

**Schwierigkeitsgrad**: Mittel  
**Vorkenntnisse**: Grundlagen der 4diac‑IDE, Umgang mit SubApps und Konstanten, Adapter‑Konzept.

**Hinweise zur Einbindung**:
- Die Konstanten `KEY_I1_STORE` und `InputNumber_I1` müssen in den entsprechenden `const`‑Ressourcen des Projekts definiert sein.
- Der Adapter muss von der aufrufenden Umgebung bereitgestellt werden (z. B. über eine HMI‑Komponente).

## Zusammenfassung

Die Übung `Uebung_012a_AX` demonstriert die effiziente Nutzung von Adaptern zur numerischen Werteingabe und deren persistente Ablage im NVS. Durch die Kapselung in einem SubApp und die Verwendung von Konstanten wird eine hohe Wiederverwendbarkeit und Konfigurierbarkeit erreicht. Der Baustein eignet sich besonders für Szenarien, in denen flexible Eingabequellen (z. B. Tastatur, Busteilsysteme) an eine einheitliche Speicherlogik angebunden werden sollen.