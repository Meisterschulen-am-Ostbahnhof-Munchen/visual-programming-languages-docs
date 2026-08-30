# Q_NumericValue_AUDI (ISOBUS Numerischer Wert - Adapter)

## Einleitung

Der `Q_NumericValue_AUDI` ist ein spezieller ISOBUS-Funktionsbaustein, der es ermöglicht, numerische Werte (`UDINT`) von einer Steuerung an ein Universal Terminal (UT) zu senden, um sie dort anzuzeigen oder zu ändern. Er nutzt `AUDI`-Adapter für die Übergabe von neuen und alten Werten, was eine moderne und typsichere Anbindung gewährleistet.

![Q_NumericValue_AUDI](Q_NumericValue_AUDI.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: `EInit` - Initialisiert den Dienst mit der `u16ObjId`.

### **Ereignis-Ausgänge**

- **INITO**: `EInit` - Bestätigt die Initialisierung.
- **CNF**: `Event` - Bestätigt die Ausführung des Dienstes.
  - Mit Variablen `STATUS` und `s16result` verknüpft.

### **Input-Variablen**

- **u16ObjId**: `UINT` - Die Objekt-ID des numerischen Eingabefeldes am ISOBUS-Terminal (Standard: `ID_NULL`).

### **Output-Variablen**

- **STATUS**: `STRING` - Statusmeldung des Dienstes (z.B. "OK", "Error").
- **s16result**: `INT` - Rückgabewert des Dienstes (Fehlercodes gemäß ISO 11783-6).

### **Adapter**

- **u32OldValue** (Plug): `AUDI` - Der alte/aktuelle Wert des Objekts.
- **u32NewValue** (Socket): `AUDI` - Der neue Wert, der an das ISOBUS-Terminal gesendet werden soll.

## Gültige Objekt-IDs

`u16ObjId` ist für dieselben Objekttypen gültig wie beim umschlossenen Basisbaustein `Q_NumericValue` (Anhang F.22, Objekte mit numerischem Wert-Attribut): Input Boolean Field (7000–7999), Input Number Field (9000–9999), Input List Field (10000–10999), Output Number Field (12000–12999), Meter (17000–17999), Linear Bar Graph (18000–18999), Arched Bar Graph (19000–19999), Number Variable (21000–21999), Object Pointer (27000–27999), Output List Object (37000–37999), External Object Pointer (43000–43999), Animation Object (44000–44999), Scaled Graphic Object (48000–48999).

ID_NULL (65535) ist kein gültiges Kommandoziel, deaktiviert aber bei `INIT` den Baustein.

## Funktionsweise

Der Baustein wird über das `INIT`-Ereignis mit der Objekt-ID `u16ObjId` initialisiert. Sobald ein Ereignis am `u32NewValue`-Socket eintrifft (`u32NewValue.E1`), wird der enthaltene UDINT-Wert (`u32NewValue.D1`) an das ISOBUS-Terminal gesendet, um den angezeigten numerischen Wert zu aktualisieren. Nach erfolgreicher Ausführung wird ein `CNF`-Ereignis ausgelöst, und der alte Wert des Objekts wird über den `u32OldValue`-Plug bereitgestellt.

## Technische Besonderheiten

✔ **ISO 11783-6 Standard**: Konforme Implementierung für ISOBUS Universal Terminals.
✔ **Adapter-basiert**: Nutzt `AUDI`-Adapter für die numerischen Werte.
✔ **Asynchroner Betrieb**: Ereignisgesteuerte Kommunikation.

## Anwendungsszenarien

- **Anzeige von Zählerständen**: Visualisierung von Zählerständen (z.B. Betriebsstunden, Stückzahlen) auf dem Terminal.
- **Sollwertvorgabe**: Übertragen von Zielwerten (z.B. Temperatur, Druck) vom ISOBUS-Terminal zur Steuerung (in Kombination mit einem NumericValue_IDA Eingangsbaustein).
- **Feedback-Systeme**: Anzeigen von Prozesswerten in Echtzeit.

## 🛠️ Zugehörige Übungen

- [Uebung_009_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_009_AX.md)
- [Uebung_083_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_083_AX.md)
