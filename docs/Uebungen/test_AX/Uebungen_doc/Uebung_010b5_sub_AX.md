Hier ist die Dokumentation für die Übung basierend auf den bereitgestellten XML-Daten.

# Uebung_010b5_sub_AX: IX auf QX (generisch)


* * * * * * * * * *

## Einleitung

Diese Sub-Applikation (`SubAppType`) mit dem Kommentar "IX auf QX (generisch)" dient dazu, eine logische Brücke zwischen einem ISOBUS-Softkey-Eingang (IX) und einem digitalen Ausgang (QX) zu schlagen. Sie ist als wiederverwendbares Modul konzipiert, das über Eingabeparameter konfiguriert wird, um spezifische Objekt-IDs auf spezifische Hardware-Ausgänge zu mappen.

## Verwendete Funktionsbausteine (FBs)

In dieser Sub-Applikation werden zwei zentrale Funktionsbausteine verschaltet, um die Kommunikation zwischen Eingabe und Ausgabe zu realisieren.

### Sub-Bausteine: Interne Logik

Hier werden die intern verwendeten Bausteine und ihre Konfiguration beschrieben.

- **Typ**: `SubAppNetwork`
- **Verwendete interne FBs**:

    - **Bausteinname**: `QXA`
        - **Typ**: `logiBUS::io::DQ::logiBUS_QXA`
        - **Parameter**: 
            - `QI` = `TRUE` (Baustein ist aktiviert)
            - `PARAMS` = "" (Leer/Unsichtbar)
        - **Dateneingang**: 
            - `Output`: Verbunden mit dem externen Eingang `Output` der Sub-Applikation.
        - **Funktionsweise**: Dieser Baustein repräsentiert die Schnittstelle zum digitalen Ausgangssystem (logiBUS DQ). Er empfängt die Konfiguration, welcher physikalische Ausgang geschaltet werden soll.

    - **Bausteinname**: `IXA`
        - **Typ**: `isobus::UT::io::Softkey::Softkey_IXA`
        - **Parameter**: 
            - `QI` = `TRUE` (Baustein ist aktiviert)
        - **Dateneingang**: 
            - `u16ObjId`: Verbunden mit dem externen Eingang `u16ObjId` der Sub-Applikation.
        - **Funktionsweise**: Dieser Baustein behandelt die Eingabeseite über ein ISOBUS Universal Terminal (UT). Er lauscht auf Ereignisse eines spezifischen Softkeys, der über die Objekt-ID definiert wird.

## Programmablauf und Verbindungen

Der Ablauf innerhalb dieser Sub-Applikation wird durch direkte Verbindungen und Adapter-Konzepte gesteuert:

1.  **Konfiguration der Schnittstellen**:
    - Die Sub-Applikation verfügt über zwei Eingänge: `u16ObjId` (vom Typ `UINT`) und `Output` (vom Typ `logiBUS::io::DQ::logiBUS_DO_S`).
    - Der Wert von `u16ObjId` wird direkt an den Baustein `IXA` weitergeleitet, um festzulegen, welcher Softkey überwacht wird.
    - Die `Output`-Definition wird direkt an den Baustein `QXA` weitergeleitet, um den zu steuernden Ausgang zu definieren.

2.  **Adapter-Verbindung**:
    - Es besteht eine **Adapter-Verbindung** zwischen `IXA.IN` (Quelle) und `QXA.OUT` (Ziel).
    - Diese Verbindung sorgt dafür, dass der Status oder die Befehle des Softkey-Bausteins (`IXA`) direkt an den Ausgangs-Baustein (`QXA`) übermittelt werden, ohne dass eine komplexe Einzelverdrahtung von Event- oder Datenleitungen notwendig ist.

**Lernziele:**
- Verständnis von Sub-Applikationen zur Kapselung von Logik.
- Nutzung von Adapter-Verbindungen zur Vereinfachung von Signalflüssen zwischen kompatiblen Bausteinen (hier zwischen ISOBUS-Input und logiBUS-Output).
- Parametrierung von generischen Bausteinen über SubApp-Schnittstellen.

## Zusammenfassung

Die `Uebung_010b5_sub_AX` stellt einen generischen Baustein dar, der flexibel eingesetzt werden kann, um eine Interaktion zwischen einem ISOBUS-Bedienelement (Softkey) und einem Aktor (Digitaler Ausgang) herzustellen. Durch die Verwendung von Adapter-Verbindungen wird die innere Komplexität minimiert und eine saubere Kapselung der Funktionalität gewährleistet.