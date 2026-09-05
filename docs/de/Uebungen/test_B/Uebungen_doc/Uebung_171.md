# Uebung_171: Exercise for E_D_FF_ANY

![Uebung_171_network](./Uebung_171_network.svg)

* * * * * * * * * *

## Einleitung

Diese Übung (`Uebung_171`) ist als Training für den Umgang mit dem Funktionsbaustein **E_D_FF_ANY** konzipiert. Sie demonstriert das Zusammenspiel zwischen IEC 61131-Funktionen zur Datenmanipulation und IEC 61499-Funktionsbausteinen zur ereignisgesteuerten Datenübertragung.

## Verwendete Funktionsbausteine (FBs)

Innerhalb dieser SubApp werden die folgenden Funktionsbausteine verwendet, um die Logik abzubilden:

### Sub-Bausteine: Enthaltene Komponenten

In dieser Übung werden spezifisch folgende Bausteine instanziiert:

-   **E_D_FF_ANY**
    -   **Typ**: `iec61499::events::E_D_FF_ANY`
    -   **Beschreibung**: Ein ereignisgesteuerter Baustein, der Daten von einem Eingang zu einem Ausgang bewegt, sobald ein Ereignis ausgelöst wird.
    -   **Verwendung in der Übung**: Dient als Empfänger des Datenwerts.

-   **F_MOVE**
    -   **Typ**: `iec61131::selection::F_MOVE`
    -   **Parameter**: `DataType` = `INT`
    -   **Beschreibung**: Eine Standard-IEC 61131 Funktion zur Zuweisung von Werten. In dieser Übung ist der Datentyp explizit auf `INT` (Integer) gesetzt.
    -   **Verwendung in der Übung**: Dient als Quelle oder Vorverarbeitung des Datenwerts, der an `E_D_FF_ANY` übergeben wird.

## Programmablauf und Verbindungen

Das Netzwerk zeigt eine einfache Verbindung zwischen einer Standard-Funktion und einem Event-Baustein, ist jedoch noch unvollständig (siehe TODO).

### Bestehende Datenverbindungen

-   **F_MOVE.OUT** $\rightarrow$ **E_D_FF_ANY.IN**: Das Ergebnis der Zuweisung/Bewegung aus dem Baustein `F_MOVE` wird direkt an den Dateneingang von `E_D_FF_ANY` geleitet.

### Hinweise zur Durchführung

Im Netzwerk befindet sich ein Kommentarbaustein mit dem Inhalt **"TODO"**. Dies deutet darauf hin, dass die Übung vom Anwender vervollständigt werden muss. Wahrscheinlich fehlen:

1.  Eingangswerte für `F_MOVE`, um einen Wert zu definieren.
2.  Eine Ereignis-Verbindung (Event Connection), um den `E_D_FF_ANY` Baustein zu triggern (Eingang `EI`), damit dieser den Datenwert übernimmt und weitergibt.

**Lernziele:**

-   Verständnis des Unterschieds zwischen reinen Datenfunktionen (`F_MOVE`) und ereignisgesteuerten Bausteinen (`E_D_FF_ANY`).
-   Korrekte Verdrahtung von Datentypen (hier `INT`).

## Zusammenfassung

Die `Uebung_171` stellt eine grundlegende Aufgabe dar, um die Datenübergabe in 4diac zu üben. Der Fokus liegt auf der korrekten Nutzung des `E_D_FF_ANY` Bausteins in Kombination mit vorangestellter IEC 61131 Logik (`F_MOVE`). Der Anwender muss die offenen Verbindungen im Sinne des "TODO"-Hinweises ergänzen, um die Funktionalität herzustellen.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
