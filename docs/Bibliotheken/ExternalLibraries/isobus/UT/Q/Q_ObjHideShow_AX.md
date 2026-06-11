# Q_ObjHideShow_AX


![Q_ObjHideShow_AX](./Q_ObjHideShow_AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **Q_ObjHideShow_AX** dient als Adapter-Wrapper für den bestehenden Baustein `Q_ObjHideShow`. Er erlaubt das einheitliche Verbergen und Anzeigen eines Objekts (Hide/Show) über einen unidirektionalen AX‑Adapter. Der Sichtbarkeitswert wird dabei als boolescher Zustand (`0` = verborgen, `1` = angezeigt) übergeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ    | Kommentar                     | Mit Variable   |
|-------|--------|-------------------------------|----------------|
| `INIT` | EInit | Service Initialization         | `u16ObjId`     |

### **Ereignis-Ausgänge**

| Name   | Typ    | Kommentar                   |
|--------|--------|-----------------------------|
| `INITO` | EInit | Bestätigung der Initialisierung |

### **Daten-Eingänge**

| Name      | Typ  | Kommentar         |
|-----------|------|-------------------|
| `u16ObjId` | UINT | Objekt‑Identifikation |

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenen Datenausgänge. Der alte Sichtbarkeitswert wird über den Plug‑Adapter `qOldVisible` ausgegeben.

### **Adapter**

| Richtung | Name          | Typ                             | Kommentar                                                  |
|----------|---------------|---------------------------------|------------------------------------------------------------|
| Socket   | `qVisible`    | `unidirectional::AX`            | Eingabe des neuen Sichtbarkeitswerts (0 = hidden, 1 = shown) |
| Plug     | `qOldVisible` | `unidirectional::AB`            | Ausgabe des bisherigen Sichtbarkeitswerts (0/1/0xFF)       |

## Funktionsweise

1. Über das Ereignis `INIT` wird der Baustein initialisiert und die Objekt‑ID (`u16ObjId`) an den internen FB `Q_ObjHideShow` übergeben.
2. Sobald am Socket `qVisible` ein Ereignis eintrifft (verbunden mit dem internen `REQ`), wird der neue Sichtbarkeitswert (`qVisible.D1`) an den internen FB weitergeleitet.
3. Der interne FB führt die Umschaltung durch und gibt über sein `CNF`‑Ereignis den alten Wert aus. Dieser wird über das Plug `qOldVisible` (Ereignis `E1` und Daten `D1`) nach außen gemeldet.
4. Der Ausgang `INITO` signalisiert den erfolgreichen Abschluss der Initialisierung.

## Technische Besonderheiten

- **Adapter‑Kapselung:** Der Baustein nutzt die standardisierten Adapter‑Typen `AX` (für Eingang) und `AB` (für Ausgang), sodass er nahtlos in adapterbasierte ISOBUS‑Netzwerke eingebunden werden kann.
- **Wiederverwendung:** Die eigentliche Logik wird durch den bewährten FB `Q_ObjHideShow` realisiert – der Wrapper fügt lediglich die Adapterschnittstelle hinzu.
- **Boolesche Steuerung:** Der Sichtbarkeitswert wird als einfacher Bool‑Wert (über `AX`‑Adapter) übertragen, was die Verwendung in typischen Ein‑/Ausschalt‑Szenarien erleichtert.

## Zustandsübersicht

Der Baustein besitzt keine explizit sichtbare Zustandsmaschine. Er durchläuft einen Initialisierungsschritt (INIT → INITO) und reagiert anschließend zyklisch auf eingehende Ereignisse am Socket `qVisible` (REQ → CNF). Der interne FB `Q_ObjHideShow` kann jedoch einen impliziten Zustand (z. B. aktuell angezeigte Sichtbarkeit) halten.

## Anwendungsszenarien

- Ein‑/Ausblenden von Bedienelementen auf einem ISOBUS‑Terminal.
- Steuerung der Anzeige von Symbolen oder Textfeldern in Abhängigkeit von Benutzereingaben oder Systemzuständen.
- Einheitliche Schnittstelle für alle Objekte, die über Adapter verbunden werden sollen.

## Vergleich mit ähnlichen Bausteinen

Der direkte FB `Q_ObjHideShow` erfordert separate Event‑ und Datenverbindungen für die Steuerung. Der wrapper‑Baustein `Q_ObjHideShow_AX` kapselt diese Verbindungen in zwei standardisierten Adaptern (AX/AB) und vereinfacht so die Integration in bestehende adapterbasierte Architekturen. Zudem wird der alte Sichtbarkeitswert automatisch über den Plug‑Adapter bereitgestellt.

## Fazit

Der **Q_ObjHideShow_AX** ist ein praktischer Wrapper, der die bewährte Funktionalität des `Q_ObjHideShow` in eine adapterbasierte Schnittstelle überführt. Er ermöglicht eine saubere, modulare Anbindung von Hide/Show‑Befehlen und erleichtert die Wiederverwendung in komplexen ISOBUS‑Steuerungssystemen.