Hier ist die Dokumentation für die Übung `Uebung_12x_sub` basierend auf den bereitgestellten XML-Daten.

# Uebung_12x_sub: Subapplication Type




* * * * * * * * * *

## Einleitung
Die Sub-Application `Uebung_12x_sub` implementiert eine Logik zur Handhabung von ISOBUS-Übertragungs-Callbacks. Sie dient dazu, zyklisch oder ereignisgesteuert Daten für eine CAN-Nachricht zu generieren, wobei der Inhalt der Nachricht (Payload) dynamisch durch einen Zähler verändert wird.

## Verwendete Funktionsbausteine (FBs)

In dieser Sub-Application werden verschiedene Funktionsbausteine kombiniert, um eine Zählerschleife zu realisieren, die ihre Werte in ein CAN-Nachrichtenformat konvertiert.

### Sub-Bausteine: Uebung_12x_sub
- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **CallbackFB**: `isobus::pgn::tx::CallbackFB`
        - **Parameter**: `DI1` = `[16#FF, 16#FF, 16#FF, 16#FF, 16#FF, 16#FF, 16#FF, 16#FF]` (Initialisierung des Daten-Arrays)
        - **Adapterverbindung**: `PLUG1` (Verbindung zum Adapter-Interface)
    - **E_CTU**: `iec61499::events::E_CTU`
        - **Typ**: Aufwärtszähler (Up Counter)
        - **Parameter**: `PV` = `UINT#0` (Prozessvariable / Limit)
    - **STRUCT_MUX**: `eclipse4diac::convert::STRUCT_MUX`
        - **Typ**: Struktur-Multiplexer zur Erstellung der CAN-Nachricht
        - **Attribute**: `StructuredType` = `isobus::pgn::CAN_MSG`
        - **Parameter**: `u16DaSize` = `0`
        - **Parameter**: `u8Priority` = `7`
    - **BYTES_TO_ARR08B**: `logiBUS::utils::conversion::arr::reversing::BYTES_TO_ARR08B`
        - **Typ**: Konverter von einzelnen Bytes zu einem Byte-Array (8 Byte)
        - **Parameter**: `IN_01` bis `IN_07` = `16#00` (Füllt die restlichen Bytes mit 0)
    - **F_USINT_TO_BYTE**: `iec61131::conversion::F_UINT_TO_BYTE`
        - **Typ**: Konverter von UINT nach BYTE (Instanzname deutet auf USINT-Nutzung hin)

- **Funktionsweise**:
    Der Sub-Baustein koordiniert den Datenfluss zwischen einem ISOBUS-Callback und der Generierung neuer Nutzdaten. Ein Zählerstand wird in ein Byte konvertiert, in ein Byte-Array integriert, in eine CAN-Nachricht verpackt und dem Callback-Baustein zur Verfügung gestellt.

## Programmablauf und Verbindungen

Der Ablauf innerhalb der Sub-Application bildet eine Rückkopplungsschleife, die bei jeder Anfrage (Request) des Callbacks den Dateninhalt aktualisiert:

1.  **Auslöser**: Der `CallbackFB` sendet ein Event über den Ausgang `REQ`.
2.  **Zählen**: Dieses Event triggert den Eingang `CU` (Count Up) des Zählers `E_CTU`, wodurch der Zählerwert erhöht wird.
3.  **Konvertierung**:
    *   Der aktuelle Zählerwert (`CV`) wird an den Baustein `F_USINT_TO_BYTE` übergeben.
    *   Nach erfolgreichem Zählen (`CUO`) wird die Konvertierung ausgelöst.
4.  **Array-Erstellung**:
    *   Das konvertierte Byte wird an den Eingang `IN_00` des `BYTES_TO_ARR08B` Bausteins geleitet. Dies ist das erste Byte der Nachricht.
    *   Die Eingänge `IN_01` bis `IN_07` sind statisch mit `0x00` belegt.
5.  **Nachrichtenerstellung**:
    *   Das erzeugte Byte-Array (`OUT`) wird an den Dateneingang `data` des `STRUCT_MUX` übergeben.
    *   Der `STRUCT_MUX` erstellt daraus eine Struktur vom Typ `isobus::pgn::CAN_MSG`.
6.  **Rückführung**:
    *   Die fertige Struktur (`OUT`) wird an den Eingang `DI1` des `CallbackFB` zurückgeführt.
    *   Das Bestätigungs-Event (`CNF`) des Multiplexers triggert das `CNF` des `CallbackFB`, um die Datenaktualisierung abzuschließen.

Diese Übung demonstriert fortgeschrittene Datenmanipulation und Event-Ketten in 4diac, insbesondere wie Adapter-Callbacks genutzt werden können, um dynamisch veränderliche Daten (hier einen hochzählenden Wert) zu senden.

## Zusammenfassung
Die `Uebung_12x_sub` stellt eine Sub-Application dar, die einen ISOBUS-Callback-Mechanismus bedient. Sie nutzt einen internen Zähler, um das erste Byte der 8-Byte Nutzlast einer CAN-Nachricht bei jedem Callback-Aufruf zu inkrementieren. Dies eignet sich hervorragend zum Testen von zyklischen Übertragungen und der korrekten Verarbeitung von Datenänderungen in einem verteilten Steuerungssystem.



## 🛠️ Zugehörige Übungen

* [Uebung_125](Uebung_125.md)
* [Uebung_126](Uebung_126.md)

