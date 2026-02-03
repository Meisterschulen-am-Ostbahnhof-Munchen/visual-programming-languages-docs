# Q_ObjHideShow

```{index} single: Q_ObjHideShow
```

![Q_ObjHideShow](https://user-images.githubusercontent.com/116869307/214148121-b8115f93-fc92-499d-ae8f-b207656d64c0.png)

* * * * * * * * * *

## Einleitung
Der **Q_ObjHideShow** ist ein standardkonformer Funktionsbaustein zur Sichtbarkeitssteuerung von Container-Objekten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.2) Spezifikation für VT-Container.

![Q_ObjHideShow](Q_ObjHideShow.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Container-Objekt-ID)
- `REQ`: Sichtbarkeitsänderungs-Anforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung

### **Daten-Eingänge**
- `u16ObjId` (UINT): Container-Objekt-ID (16-bit)
- `qVisible` (BOOL): Sichtbarkeitsstatus (TRUE=anzeigen, FALSE=verstecken)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `qOldVisible` (BOOL): Vorheriger Sichtbarkeitsstatus
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Container-Objekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Sichtbarkeitsänderung**:
   - `REQ` mit gewünschtem Sichtbarkeitsstatus
   - Ändert die Darstellung des Containers und aller enthaltenen Objekte
   - `CNF` liefert Betriebsstatus und vorherigen Zustand

3. **Spezialfälle**:
   - Bei ungültigen Objekt-IDs wird VT_E_HANDLE_INVALID zurückgegeben

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.2)
✔ **Kaskadierender Effekt** (Beeinflusst enthaltene Objekte)
✔ **Sofortige GUI-Aktualisierung**
✔ **Zustandserhaltung** (Merkt vorherigen Status)

## Statusreferenz

| qVisible | Containerzustand     |
|----------|----------------------|
| FALSE (0)| Unsichtbar           |
| TRUE (1) | Sichtbar             |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Ausführung           |
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Container-ID            |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |

## Anwendungsszenarien

- **Dynamische Oberflächen**: Kontextabhängige Anzeigen
- **Bildschirmmanager**: View-Wechsel
- **Alarmmanagement**: Störmeldungscontainer
- **Benutzerführung**: Schrittweise Anleitungen

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | Q_ObjHideShow | VtContainerControl | VtVisibilityManager |
|---------------|---------------|--------------------|---------------------|
| ISO-Standard  | ✔             | ✖                  | ✖                   |
| Containerfokus| ✔             | ✔                  | ✖                   |
| Kaskadierend  | ✔             | ✖                  | ✔                   |
| Rückmeldung   | ✔             | ✖                  | ✔                   |






## 🛠️ Zugehörige Übungen

* [Uebung_014](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_014.md)

## Fazit

Der Q_ObjHideShow-Baustein bietet zentrale Sichtbarkeitskontrolle:

- **Effizient**: Sofortige GUI-Aktualisierung
- **Umfassend**: Beeinflusst gesamte Containerelemente
- **Zuverlässig**: ISO-konforme Implementierung

Essential für:
- Adaptive Benutzeroberflächen
- Komplexe Maskenhierarchien
- Zustandsgesteuerte Visualisierungen