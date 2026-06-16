# AUDI_DEMUX_2


![AUDI_DEMUX_2](./AUDI_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AUDI_DEMUX_2` ist ein generischer 1‑zu‑2‑Demultiplexer für den unidirektionalen Adaptertyp `AUDI`. Er leitet einen eingehenden AUDI‑Wert an einen von zwei Ausgangs‑Plugs weiter, gesteuert durch einen numerischen Index.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mit Daten |
|----------|--------------|-----------|
| `REQ`    | Anforderung zum Weiterleiten des aktuellen Eingangswerts gemäß Index `K` | `K` |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigung, dass die Weiterleitung abgeschlossen ist |

### **Daten-Eingänge**

| Name | Typ   | Beschreibung |
|------|-------|--------------|
| `K`  | `UINT` | Auswahlindex (0 → OUT1, 1 → OUT2) |

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Rolle        | Name   | Typ                      | Richtung   | Beschreibung                     |
|--------------|--------|--------------------------|------------|----------------------------------|
| Socket       | `IN`   | `adapter::types::unidirectional::AUDI` | Eingang    | Eingangswert, der demultiplext wird |
| Plug         | `OUT1` | `adapter::types::unidirectional::AUDI` | Ausgang    | Erster Ausgang (Index 0)         |
| Plug         | `OUT2` | `adapter::types::unidirectional::AUDI` | Ausgang    | Zweiter Ausgang (Index 1)        |

## Funktionsweise
Der Baustein wartet in einem Grundzustand auf das Ereignis `REQ`. Beim Eintreffen von `REQ` wird der aktuelle Wert des Daten‑Eingangs `K` ausgewertet:
- **K = 0**: Der am Socket `IN` anliegende AUDI‑Wert wird an den Plug `OUT1` weitergeleitet.
- **K = 1**: Der Wert wird an den Plug `OUT2` weitergeleitet.
- **K > 1**: Das Verhalten ist undefiniert; die Weiterleitung erfolgt nicht oder an einen nicht spezifizierten Ausgang.

Nach erfolgreicher Weiterleitung wird das Ereignis `CNF` ausgegeben, und der Baustein kehrt in den Bereitschaftszustand zurück.

## Technische Besonderheiten
- Der Baustein ist als generischer Funktionsbaustein (`GEN_AUDI_DEMUX`) realisiert und kann durch die Angabe einer konkreten Typ‑Hash‑Kennung für unterschiedliche AUDI‑Varianten parametrisiert werden.
- Die Schnittstelle verwendet ausschließlich den unidirektionalen Adapter `AUDI`, der in einem Adapter‑Package definiert ist.
- Die Logik ist ereignisgesteuert und eignet sich für zyklische sowie ereignisgetriebene Automatisierungsumgebungen.

## Zustandsübersicht
Der Baustein besitzt implizit einen internen Zustandsautomaten:
- **START**: Baustein ist initialisiert und bereit.
- **Warte auf REQ**: Grundzustand.
- **Verarbeite**: Nach Eintreffen von `REQ` wird die Weiterleitung durchgeführt; in dieser Phase wird kein weiteres `REQ` akzeptiert.
- **Rückkehr**: Nach Ausgabe von `CNF` wird wieder in den Grundzustand gewechselt.

## Anwendungsszenarien
- **Signaldemultiplexing in der Landtechnik**: Verteilung eines AUDI‑Signals (z. B. Sensordaten) auf zwei verschiedene Steuerungseinheiten.
- **Umschaltung zwischen Betriebsmodi**: Je nach Index wird ein Signal an eine andere Verarbeitungseinheit geleitet.
- **Test- und Diagnoseaufgaben**: Gezielte Zuführung eines Testsignals an einen von zwei Ausgängen.

## Vergleich mit ähnlichen Bausteinen
- `AUDI_DEMUX_2` unterscheidet sich von allgemeinen Demultiplexern (z. B. `DEMUX` für elementare Datentypen) durch die Verwendung des komplexen Adaptertyps `AUDI`.
- Verglichen mit einem Multiplexer (`AUDI_MUX`) kehrt die Datenflussrichtung um – hier wird ein Signal auf mehrere Ausgänge verteilt, während ein Multiplexer mehrere Eingänge auf einen Ausgang zusammenführt.

## Fazit
`AUDI_DEMUX_2` ist ein spezialisierter, generischer Demultiplexer für unidirektionale AUDI‑Schnittstellen. Er ermöglicht eine saubere und ereignisgesteuerte Verteilung von Signalen in Automatisierungssystemen, insbesondere in Umgebungen, die den AUDI‑Adapterstandard nutzen. Die einfache Schnittstelle (ein Index, zwei Ausgänge) macht ihn intuitiv einsetzbar und leicht in bestehende Steuerungslogiken integrierbar.