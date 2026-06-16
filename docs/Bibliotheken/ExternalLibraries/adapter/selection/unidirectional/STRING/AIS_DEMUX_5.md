# AIS_DEMUX_5


![AIS_DEMUX_5](./AIS_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AIS_DEMUX_5** ist ein generischer AIS-Demultiplexer (Generic FB) gemäß IEC 61499. Er dient dazu, ein über den Adapter-Eingang **IN** ankommendes AIS-Signal je nach eingestelltem Index **K** auf einen von fünf Adapter-Ausgängen (**OUT1** … **OUT5**) weiterzuleiten. Die Auswahl und Weiterleitung wird durch ein Ereignis **REQ** angestoßen und nach erfolgreicher Übertragung mit **CNF** quittiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Mit Variablen | Beschreibung                                      |
|----------|---------------|---------------------------------------------------|
| **REQ**  | K             | Setzt den Index **K** und startet die Demultiplex-Aktion |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung                                   |
|----------|------------------------------------------------|
| **CNF**  | Bestätigung, dass der Demultiplex-Vorgang abgeschlossen ist |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung                            |
|----------|-------|-----------------------------------------|
| **K**    | UINT  | Index des gewünschten Ausgangs (1 … 5)  |

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über die Adapter-Schnittstellen.

### **Adapter**

| Richtung | Adapter     | Typ                                  | Beschreibung                                          |
|----------|-------------|--------------------------------------|-------------------------------------------------------|
| Sockel   | **IN**      | adapter::types::unidirectional::AIS  | Eingangs-AIS-Signal, das auf die Ausgänge verteilt wird |
| Plug     | **OUT1**    | adapter::types::unidirectional::AIS  | Erster AIS-Ausgang                                    |
| Plug     | **OUT2**    | adapter::types::unidirectional::AIS  | Zweiter AIS-Ausgang                                   |
| Plug     | **OUT3**    | adapter::types::unidirectional::AIS  | Dritter AIS-Ausgang                                   |
| Plug     | **OUT4**    | adapter::types::unidirectional::AIS  | Vierter AIS-Ausgang                                   |
| Plug     | **OUT5**    | adapter::types::unidirectional::AIS  | Fünfter AIS-Ausgang                                   |

## Funktionsweise

1. Der Anwender stellt den gewünschten Ausgangsindex **K** (1 … 5) ein.
2. Ein steigendes Ereignis an **REQ** löst die Demultiplex-Aktion aus:
   - Der aktuelle Wert vom Adapter-Eingang **IN** wird gelesen.
   - Anschließend wird dieser Wert auf den Adapter-Ausgang **OUTx** (x = K) geschrieben.
3. Nach erfolgreichem Schreiben wird das Ereignis **CNF** ausgegeben.
4. Bei einem Index außerhalb des zulässigen Bereichs (z. B. 0 oder >5) wird keine Aktion ausgeführt und **CNF** dennoch gesendet (oder verhaltenabhängig – typischerweise erfolgt keine Zuordnung).

Die interne Verarbeitung ist ereignisgesteuert und erfolgt nach dem Prinzip der klassischen Demultiplexer: Ein Eingang wird auf einen von mehreren Ausgängen geschaltet.

## Technische Besonderheiten

- **Generischer Baustein (Generic FB):** Der Funktionsblock ist als generische Vorlage `GEN_AIS_DEMUX` ausgelegt. Die vorliegende Instanz `AIS_DEMUX_5` ist eine spezielle Ausprägung mit genau fünf Ausgängen. Durch Anpassung des generischen Typs können Demultiplexer mit beliebig vielen Ausgängen erzeugt werden.
- **Adapter‑basierte Ein‑/Ausgabe:** Statt herkömmlicher Daten‑Ein‑/Ausgänge verwendet der Block gerichtete Adapter vom Typ `AIS`. Dies ermöglicht eine saubere, komponentenorientierte Verbindung komplexer Signaltypen in der IEC‑61499‑Umgebung.
- **Fehlerbehandlung:** Bei ungültigem Index **K** wird der eingehende Wert an keinen Ausgang weitergegeben; das Bestätigungssignal **CNF** wird dennoch ausgegeben, um den aufrufenden Block nicht zu blockieren.

## Zustandsübersicht

Der interne Zustandsautomat ist einfach gehalten:

```
[IDLE] → REQ (mit gültigem K) → [WRITE] → CNF → [IDLE]
                                  ↑
                     Bei ungültigem K: sofort CNF, kein Schreiben
```

- **IDLE:** Warten auf ein REQ-Ereignis.
- **WRITE:** Werteübertragung von **IN** auf den ausgewählten **OUTx**.
- Nach Abschluss (oder bei Fehler) wird **CNF** gesendet und der Automat kehrt in den IDLE‑Zustand zurück.

## Anwendungsszenarien

- **Sensor‑Selektion:** Ein einziger AIS‑Sensor (z. B. ein analoger Füllstandssensor) kann je nach Anforderung auf verschiedene Aktoren (Ventile, Pumpen) geschaltet werden.
- **Test- und Diagnosesysteme:** Umschalten eines Testsignals nacheinander auf mehrere zu prüfende Geräte.
- **Routing‑Aufgaben:** Dynamische Verteilung eines Datenstroms an verschiedene Verbraucher in einer Automatisierungsanlage.

## Vergleich mit ähnlichen Bausteinen

| Baustein           | Beschreibung |
|--------------------|--------------|
| **AIS_DEMUX_5**    | Demultiplexer für AIS‑Adapter mit 5 Ausgängen |
| **AIS_SELECT**     | Multiplexer (Auswahl eines von mehreren Eingängen) |
| **GEN_DEMUX** (generisch) | Allgemeiner Demultiplexer für einfache Datentypen (z. B. INT, REAL) – ohne Adapter |

Im Gegensatz zu einem einfachen Daten‑Demultiplexer arbeitet `AIS_DEMUX_5` auf einer abstrakteren Adapter‑Ebene und kapselt die gesamte Signalübertragung (inkl. Konsistenzprüfungen) im Adapter‑Protokoll.

## Fazit

Der **AIS_DEMUX_5** ist ein kompakter, generischer Funktionsblock der IEC‑61499‑Bibliothek, der eine saubere Adapter‑basierte Demultiplex‑Funktionalität für AIS‑Signale bereitstellt. Durch die generische Vorlage kann er flexibel an die Anzahl der benötigten Ausgänge angepasst werden. Die einfache ereignisgesteuerte Schnittstelle macht ihn leicht in übergeordnete Steuerungslogiken integrierbar, während die Verwendung von Adaptern eine hohe Wiederverwendbarkeit und Kapselung gewährleistet.