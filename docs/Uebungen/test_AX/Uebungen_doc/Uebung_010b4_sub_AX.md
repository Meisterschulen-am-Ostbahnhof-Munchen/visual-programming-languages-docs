Hier ist die Dokumentation für die Übung `Uebung_010b4_sub_AX`, basierend auf den bereitgestellten XML-Daten.

# Uebung_010b4_sub_AX: IX auf QX (generisch)


* * * * * * * * * *

## Einleitung

Diese Übung behandelt die Erstellung einer **Sub-Applikation** (SubApp), die eine generische Verknüpfung zwischen einem ISOBUS-Eingangselement (Softkey) und einem logiBUS-Ausgang herstellt. Das Ziel ist es, eine Softkey-Eingabe (`IX`) direkt auf einen digitalen Ausgang (`QX`) zu mappen. Durch die Verwendung von Schnittstellenvariablen ist dieser Baustein wiederverwendbar für verschiedene Objekt-IDs und Ausgänge.

## Verwendete Funktionsbausteine (FBs)

In dieser Übung wird eine Sub-Applikation definiert, die intern zwei spezialisierte Kommunikationsbausteine verwendet, um die Signalverarbeitung zwischen ISOBUS und logiBUS zu realisieren.

### Sub-Bausteine: Uebung_010b4_sub_AX

- **Typ**: SubAppType
- **Beschreibung**: IX auf QX (generisch)
- **Verwendete interne FBs**:

    - **IXA**: `isobus::UT::io::Softkey::Softkey_IXA`
        - **Parameter**: 
            - `QI` = `TRUE` (Baustein ist aktiv)
        - **Dateneingang**: 
            - `u16ObjId` (Verbunden mit der Schnittstelle `u16ObjId`)
        - **Adapterausgang**: 
            - `IN` (Verbunden mit `QXA.OUT`)
    
    - **QXA**: `logiBUS::io::DQ::logiBUS_QXA`
        - **Parameter**: 
            - `QI` = `TRUE` (Baustein ist aktiv)
        - **Dateneingang**: 
            - `Output` (Verbunden mit der Schnittstelle `Output`)
        - **Adaptereingang**: 
            - `OUT` (Verbunden mit `IXA.IN`)

- **Funktionsweise**:
    Dieser Sub-Baustein fungiert als Brücke. Er nimmt eine Objekt-ID (`u16ObjId`) entgegen, die einen Softkey auf einem ISOBUS-Universal-Terminal (UT) identifiziert. Gleichzeitig nimmt er eine Ausgangskonfiguration (`Output`, Typ `logiBUS_DO_S`) entgegen, die bestimmt, welcher physische Ausgang geschaltet werden soll. 
    
    Innerhalb des Netzwerks wird der Softkey-Status über den Baustein `IXA` erfasst. Anstatt diskrete Events und Booleans zu verdrahten, nutzt diese Implementierung eine **Adapter-Verbindung**. Der Adapter-Port `IN` des Softkey-Bausteins (`IXA`) ist direkt mit dem Adapter-Port `OUT` des Ausgangs-Bausteins (`QXA`) verbunden. Dies ermöglicht eine direkte Durchleitung des Zustands (z.B. Tastendruck) auf den Hardware-Ausgang.

## Programmablauf und Verbindungen

Das Netzwerk innerhalb der Sub-Applikation ist minimal gehalten und verlässt sich auf die Abstraktion durch Adapter.

1.  **Schnittstellen-Eingänge**:
    *   **u16ObjId (UINT)**: Hier wird die ID des Softkeys übergeben (Initialwert: `ID_NULL`). Diese Variable wird intern an `IXA.u16ObjId` weitergeleitet.
    *   **Output (logiBUS_DO_S)**: Hier wird der Ziel-Ausgang definiert (z.B. Output_Q1..Q8). Diese Variable wird intern an `QXA.Output` weitergeleitet.

2.  **Interne Logik**:
    *   Der Baustein `IXA` initialisiert die Kommunikation mit dem Softkey unter der angegebenen ID.
    *   Der Baustein `QXA` initialisiert die Ansteuerung des gewählten digitalen Ausgangs.
    *   Die Verbindung zwischen Eingabe und Ausgabe erfolgt nicht über klassische `AND`/`OR` Logik oder Event-Trigger (`INIT`, `REQ`, `CNF`), sondern über die **Adapter-Verbindung** (`Connection Source="IXA.IN" Destination="QXA.OUT"`). Dies abstrahiert den Signalfluss und sorgt dafür, dass der Ausgang dem logischen Zustand des Eingangsadapters folgt.

**Anwendungshinweise:**
*   Dieser Baustein ist als generisches Modul gedacht. Er kann mehrfach im Hauptprogramm instanziiert werden, um verschiedene Tasten auf verschiedene Ausgänge zu legen, ohne die interne Logik neu programmieren zu müssen.
*   Es werden keine expliziten Events nach außen geführt; die Steuerung erfolgt rein intern über die Bus-Treiber.

## Zusammenfassung

Die `Uebung_010b4_sub_AX` stellt ein kompaktes Modul zur direkten Kopplung eines ISOBUS-Softkeys an einen digitalen logiBUS-Ausgang dar. Durch die Kapselung in einer Sub-Applikation und die Nutzung von Adaptern wird die Komplexität der zugrundeliegenden Protokolle verborgen, was eine einfache und schnelle Zuweisung von Tasten zu Ausgängen in übergeordneten Anwendungen ermöglicht.