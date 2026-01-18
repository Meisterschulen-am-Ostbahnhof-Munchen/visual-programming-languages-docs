# Q_NumericValue_AUDI (ISOBUS Numerischer Wert - Adapter)

```{index} single: Q_NumericValue_AUDI (ISOBUS Numerischer Wert - Adapter)
```

## 🎧 Podcast

* [Das Working Set Objekt: Das Gehirn der ISOBUS-Bedienoberfläche verstehen – Von der Norm zur Praxis im ISO-Designer](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/Das-Working-Set-Objekt-Das-Gehirn-der-ISOBUS-Bedienoberflche-verstehen--Von-der-Norm-zur-Praxis-im-ISO-Designer-e36cl5v)
* [ISOBUS Button: Mehr als nur ein Klick – Die Standardisierung der Landtechnik](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Button-Mehr-als-nur-ein-Klick--Die-Standardisierung-der-Landtechnik-e3673rb)
* [ISOBUS Object Pointer: Das Geheimnis dynamischer Displays und effizienter Fehlerdiagnose](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Object-Pointer-Das-Geheimnis-dynamischer-Displays-und-effizienter-Fehlerdiagnose-e36bp75)
* [ISOBUS Output Meter: Dynamische Anzeigen meistern – vom Zeiger bis zur Visualisierung auf dem VT](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Output-Meter-Dynamische-Anzeigen-meistern--vom-Zeiger-bis-zur-Visualisierung-auf-dem-VT-e36t2tp)
* [ISOBUS Skalierung: Wenn der Ackerschlepper-Bildschirm nicht passt – Eine Einführung in ISO 11783-6](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Skalierung-Wenn-der-Ackerschlepper-Bildschirm-nicht-passt--Eine-Einfhrung-in-ISO-11783-6-e36a8q6)

## 📺 Video

* [2025-11-04 20-15-06 LogiBUS® auf dem Weg zu Eclipse 4diac™ 3.0 - noch mehr Adapter (AX)](https://www.youtube.com/watch?v=RsY65VqTAMc)
* [Das Working Set Objekt: Das Gehirn der ISOBUS-Bedienoberfläche verstehen – Von der Norm zur Praxi...](https://www.youtube.com/watch?v=SiRvrecE_7I)
* [From Control Box to Custom ISOBUS  A DIY Guide](https://www.youtube.com/watch?v=tlsRGZIfh9I)
* [ISOBUS-Bedienoberflächen: Wenn Tasten und Hauptanzeige unterschiedlich skalieren – ISO 11783-6 en...](https://www.youtube.com/watch?v=kQM4MLsyj5U)
* [ISOBUS: The Secret Language](https://www.youtube.com/watch?v=Fezbc5Acd24)

## Einleitung
Der `Q_NumericValue_AUDI` ist ein spezieller ISOBUS-Funktionsbaustein, der es ermöglicht, numerische Werte (`UDINT`) von einer Steuerung an ein Universal Terminal (UT) zu senden, um sie dort anzuzeigen oder zu ändern. Er nutzt `AUDI`-Adapter für die Übergabe von neuen und alten Werten, was eine moderne und typsichere Anbindung gewährleistet.

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