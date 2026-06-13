# Uebung_012c_AUDI: Numeric Value Input und Speichern INI mit Subapp (Adapter Version)



* * * * * * * * * *

## Einleitung

Diese Übung demonstriert die Realisierung einer numerischen Werteingabe mit anschließender Speicherung in einem nichtflüchtigen Speicher (NVS) unter Verwendung einer SubApp. Das Besondere ist die Nutzung einer SubApp in der **Adapter-Version**, welche es ermöglicht, die Ein- und Ausgänge über einen Adapter-Mechanismus zu kapseln. Die SubApp **Uebung_012c_AUDI** enthält einen vorgefertigten Sub-Baustein, der den gesamten Prozess der Eingabe und Speicherung übernimmt.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: Uebung_012c_sub_AUDI

- **Typ**: `MyLib::sys::INI_IN_AND_STORE_AUDI`
- **Verwendete interne FBs**: Die internen FBs dieses Bausteins sind nicht im Detail einsehbar, da es sich um einen vordefinierten Baustein aus der Bibliothek `MyLib::sys` handelt. Er besteht vermutlich aus einer Kette von Bausteinen für die Wertaufnahme, Konvertierung und die NVS-Speicherung.
- **Funktionsweise**: Der Baustein liest einen numerischen Wert aus dem `DefaultPool` unter der Objekt-ID `InputNumber_I1` (importiert aus `Uebungen::const::UT::DefaultPool`). Diesen Wert speichert er im nichtflüchtigen Speicher (NVS) unter dem Schlüssel `KEY_I1_STORE` in der Sektion `SECTION_I1_STORE` (beide importiert aus `Uebungen::const::NVS::NVS_Keys`). Die Parameter `KEY`, `SECTION` und `u16ObjId` werden der SubApp beim Einfügen übergeben.

#### Parameter des Sub-Bausteins:

| Parameter    | Wert                  | Quelle / Bedeutung                                       |
|--------------|-----------------------|----------------------------------------------------------|
| `KEY`        | `KEY_I1_STORE`        | Konstante: Schlüssel für den NVS-Eintrag                 |
| `SECTION`    | `SECTION_I1_STORE`    | Konstante: Sektion in der NVS-Struktur                   |
| `u16ObjId`   | `InputNumber_I1`      | Objekt-ID aus dem DefaultPool, die den Eingabewert liefert |

## Programmablauf und Verbindungen

Die Haupt-SubApp `Uebung_012c_AUDI` besitzt **keine eigenen Ein-/Ausgangsschnittstellen** (`SubAppInterfaceList` ist leer). Der gesamte Funktionsumfang wird durch den eingebetteten Sub-Baustein `Uebung_012c_sub_AUDI` abgedeckt.

- **Ablauf**: Sobald die SubApp aktiviert wird (z. B. durch einen übergeordneten Baustein), startet der Sub-Baustein `INI_IN_AND_STORE_AUDI` seinen internen Ablauf. Er holt den aktuellen Wert der Spannweite `InputNumber_I1` aus dem `DefaultPool` und speichert diesen persistent im NVS unter den angegebenen Schlüssel- und Sektionskonstanten.
- **Verbindungen**: Es sind keine expliziten Daten- oder Ereignisverbindungen innerhalb der SubApp sichtbar, da der Sub-Baustein seine Funktionalität vollständig intern kapselt. Die SubApp dient als Wrapper, um die Konfiguration (über Parameter) zu ermöglichen und die Wiederverwendung zu vereinfachen.
- **Lernziele**: Verständnis für die Verwendung von SubApps in 4diac, insbesondere als Adapter-Version. Kennenlernen der NVS-Speicherung sowie der Verknüpfung von Eingabewerten aus einem DefaultPool mit persistenten Speicherorten.
- **Schwierigkeitsgrad**: Mittel – Grundlegende Kenntnisse in 4diac und der Funktionsblock-Modellierung werden vorausgesetzt.

## Zusammenfassung

Die Übung *Uebung_012c_AUDI* zeigt, wie ein numerischer Wert über eine vordefinierte SubApp (Adapter-Version) eingelesen und in einem nichtflüchtigen Speicher abgelegt wird. Dabei kommen Konstanten für Schlüssel und Sektion sowie eine Objekt-ID aus dem DefaultPool zum Einsatz. Der Lernende erhält Einblick in die Kapselung von Funktionslogik durch SubApps und in die Handhabung der NVS-Bibliothek in 4diac.