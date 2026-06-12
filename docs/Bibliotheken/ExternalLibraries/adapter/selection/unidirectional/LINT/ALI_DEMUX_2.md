# ALI_DEMUX_2


![ALI_DEMUX_2](./ALI_DEMUX_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALI_DEMUX_2** ist ein generischer Demultiplexer für den ALI‑Adaptertyp. Er leitet den an einem Eingangsadapter anliegenden Wert wahlweise an einen von zwei Ausgangsadaptern weiter. Die Auswahl des aktiven Ausgangs erfolgt über einen Index, der über einen Ereigniseingang gesetzt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `REQ`    | Setzt den Index `K` und leitet den Eingangswert an den entsprechenden Ausgang weiter. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF`    | Bestätigt die erfolgreiche Weiterleitung (ohne zusätzliche Daten). |

### **Daten-Eingänge**

| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| `K`      | UINT  | Index des auszuwählenden Ausgangs (1 oder 2). |

### **Daten-Ausgänge**

Keine separaten Datenausgänge – die Ausgabe erfolgt über die Adapter.

### **Adapter**

| Typ          | Richtung | Bezeichnung | Kommentar                             |
|--------------|----------|-------------|---------------------------------------|
| ALI          | Eingang  | `IN`        | Der zu demultiplexende Eingangswert.  |
| ALI          | Ausgang  | `OUT1`      | Erster Ausgangskanal (Index 1).       |
| ALI          | Ausgang  | `OUT2`      | Zweiter Ausgangskanal (Index 2).      |

## Funktionsweise

Ein Ereignis am Eingang `REQ` löst die Verarbeitung aus. Der Wert des Parameters `K` bestimmt, an welchen der beiden Ausgangsadapter (`OUT1` oder `OUT2`) der über `IN` anliegende Wert weitergeleitet wird. Nach der Weiterleitung wird am Ausgang `CNF` ein Ereignis gesendet.

Die Zuordnung erfolgt wie folgt:
- Ist `K = 1`, wird der Wert an `OUT1` übergeben.
- Ist `K = 2`, wird der Wert an `OUT2` übergeben.
- Für andere Werte von `K` ist das Verhalten undefiniert (keine Ausgabe).

Der Baustein arbeitet rein signalbezogen – es findet keine dauerhafte Verbindung statt, sondern nur eine einmalige Weiterleitung pro REQ‑Ereignis.

## Technische Besonderheiten

- **Generischer Adaptertyp** – Der Baustein nutzt den standardisierten unidirektionalen ALI‑Adapter, der in vielen IEC‑61499‑Bibliotheken verfügbar ist.
- **Indizierung über UINT** – Der Index `K` ist als vorzeichenloser 16‑Bit‑Wert definiert, erlaubt theoretisch eine Erweiterung auf mehr als zwei Ausgänge (hier jedoch auf zwei begrenzt).
- **Ereignisgesteuerte Verarbeitung** – Die Weiterleitung erfolgt nur auf ein explizites `REQ`‑Ereignis hin, nicht zyklisch.
- **Keine Datenvalidierung** – Es wird nicht geprüft, ob `K` im erlaubten Bereich liegt; die Anwendung muss dies sicherstellen.

## Zustandsübersicht

Der ALI_DEMUX_2 besitzt keine expliziten Zustände im Sinne eines Zustandsautomaten. Nach dem Empfang von `REQ` wird die Operation sofort ausgeführt und das `CNF`‑Ereignis gesendet. Der Baustein ist stets bereit für den nächsten Auftrag.

## Anwendungsszenarien

- **Signalverteilung** – Ein von einer Sensoreinheit erfasstes ALI‑Signal soll wahlweise an eine von zwei nachgelagerten Verarbeitungskomponenten gesendet werden.
- **Umschaltung zwischen Betriebsarten** – Je nach Betriebsmodus (Indizes 1 oder 2) wird der Datenstrom in unterschiedliche Aktor- oder Steuerbausteine geleitet.
- **Test- oder Simulationsumgebungen** – Ein generiertes Testsignal kann dynamisch zwischen verschiedenen Prüfpfaden umgeschaltet werden.

## Vergleich mit ähnlichen Bausteinen

Gegenüber einem herkömmlichen Data‑Demultiplexer (z. B. `DEMUX`), der Werte über Datenports weitergibt, arbeitet der ALI_DEMUX_2 auf Basis von **Adaptern**. Adapter kapseln komplexe Schnittstellen, sodass mehrere Daten und Ereignisse gleichzeitig über einen Port übertragen werden können. Dies vereinfacht die Verschaltung in größeren Architekturen, erfordert aber, dass alle beteiligten Komponenten den gleichen Adaptertyp (hier ALI) verwenden.

Ein reiner Daten‑Demux hätte separate Datenausgänge; hier sind die Ausgänge als Adapter realisiert, was die Struktur modularer macht, aber auch spezifischer.

## Fazit

Der ALI_DEMUX_2 ist ein kompakter und nützlicher Baustein zur Signalweiterleitung in ALI‑basierten Systemen. Durch die ereignisgesteuerte Auswahl und die Verwendung von Adaptern fügt er sich nahtlos in moderne IEC‑61499‑Anwendungen ein. Seine Einfachheit und klare Funktionalität machen ihn zu einem soliden Grundbaustein für jegliche Umschaltlogik.