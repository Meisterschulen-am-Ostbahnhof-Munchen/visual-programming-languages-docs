# ADI_D_FF_TMIN


![ADI_D_FF_TMIN](./ADI_D_FF_TMIN.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **ADI_D_FF_TMIN** realisiert ein Daten-Latch (D‑Flip‑Flop) mit einer konfigurierbaren Mindestverweilzeit zwischen zwei aufeinanderfolgenden Übernahmeereignissen. Er dient dazu, einen Datenwert zu einem bestimmten Ereigniszeitpunkt zu sichern und erst dann wieder zu aktualisieren, wenn eine vorgegebene Zeitspanne (Tmin) seit der letzten Übergabe verstrichen ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| INIT | EInit | Init‑Anforderung; Übergibt den Parameter Tmin |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| INITO | EInit | Init‑Bestätigung |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| Tmin | TIME | Mindestzeit zwischen zwei Ereignissen am Eingang I.E1 |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – der gelatchte Wert wird über den Adapter‑Ausgang Q bereitgestellt.

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket (Eingang) | I | adapter::types::unidirectional::ADI | Wert und Ereignis zum Latchen |
| Plug (Ausgang) | Q | adapter::types::unidirectional::ADI | Gelatchter Wert und zugehöriges Ausgangsereignis |

## Funktionsweise
Der FB empfängt über den Adapter‑Socket **I** ein Ereignis (I.E1) samt einem Datenwert (I.D1). Nach diesem Ereignis wird der Wert übernommen und am Adapter‑Plug **Q** als Q.D1 ausgegeben; gleichzeitig wird ein Ereignis an Q.E1 gesendet.  
Zwischen zwei aufeinanderfolgenden Übernahmen muss jedoch mindestens die in **Tmin** festgelegte Zeit vergangen sein. Solange diese Mindestfrist nicht abgelaufen ist, wird ein eingehendes Ereignis an I.E1 ignoriert (der Wert bleibt unverändert).  
Der INIT‑Eingang setzt den Parameter Tmin und bestätigt dies über INITO, ohne das Flip‑Flop selbst zu beeinflussen.

Der FB nutzt intern den Baustein `iec61499::events::E_D_FF_ANY_TMIN`, der die eigentliche Logik (D‑Flip‑Flop mit Zeitsteuerung) kapselt.

## Technische Besonderheiten
- **Adapter‑basierte Schnittstelle:** Statt direkt verschalteter Ereignis‑ und Datenports werden die Ein‑ und Ausgänge über uni‑direktionale Adapter (Typ `ADI`) realisiert. Dies vereinfacht die Wiederverwendung und Trennung von Steuerungs‑ und Datenflüssen.
- **Mindestzeit‑Garantie:** Die Tmin‑Zeit wird ab dem Moment des letzten gültigen Ausgangsereignisses gemessen. Bei einem zu frühen Eingangsereignis bleibt der Ausgang unverändert – der alte Wert bleibt erhalten.
- **Initialisierung notwendig:** Der Baustein muss zunächst über INIT mit einem Tmin‑Wert initialisiert werden, bevor er auf eingehende Adapter‑Ereignisse reagiert.

## Zustandsübersicht
Der FB besitzt eine implizite Zustandslogik, die durch den internen `E_D_FF_ANY_TMIN` abgebildet wird:
- **Idle:** Warten auf das erste gültige Ereignis an I.E1 nach der Initialisierung.
- **Latched:** Ein Wert wurde übernommen; die Zeitmessung für Tmin läuft. Neue Ereignisse an I.E1 werden solange ignoriert, bis Tmin abgelaufen ist.
- **Ready:** Tmin ist abgelaufen; der Baustein ist bereit für die nächste Übernahme.

Die Zustandsübergänge werden durch die Ereignisse I.E1 und den internen Timer gesteuert. Eine Initialisierung setzt den Baustein zurück in den Idle‑Zustand.

## Anwendungsszenarien
- **Taktentkopplung in Industrieanwendungen:** Sicherstellen, dass Daten nur in definierten Mindestabständen übernommen werden (z. B. bei Sensorabfragen mit fester Rasterzeit).
- **Entprellung von Ereignissen:** Vermeidung von Doppelauswertungen bei kurz aufeinanderfolgenden Ereignissen (z. B. Taster‑ oder Schaltsignale mit Prellzeit).
- **Datenhaltung in sicherheitskritischen Systemen:** Einmal gelatchte Werte bleiben solange gültig, bis die Mindestzeit abgelaufen ist – schützt vor Rauschen oder transienten Störungen.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑D‑Flip‑Flop (ohne Tmin):** Ein einfacher D‑FF wie z. B. `E_D_FF` übernimmt jeden Wert sofort bei jedem Ereignis. Der vorliegende Baustein erweitert dies um eine zeitliche Sperre.
- **E_D_FF_ANY_TMIN:** Dies ist der direkte interne Basisbaustein. `ADI_D_FF_TMIN` kapselt dessen Funktionalität und bietet eine Adapter‑Schnittstelle anstelle separater Ereignis‑/Datenports – dies erhöht die Flexibilität bei der Verschaltung mit anderen adapterbasierten Komponenten.

## Fazit
Der `ADI_D_FF_TMIN` ist ein nützlicher Funktionsblock für Anwendungen, die eine zuverlässige Datenübernahme mit einstellbarer zeitlicher Entkopplung erfordern. Die Verwendung von Adaptern macht ihn besonders geeignet für modulare, adapterbasierte Architekturen nach IEC 61499. Durch die Mindestzeit wird die Stabilität des Gesamtsystems in Umgebungen mit sporadischen oder prellbehafteten Ereignissen erhöht.