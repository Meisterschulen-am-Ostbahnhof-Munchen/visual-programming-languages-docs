# AIWS_D_FF


![AIWS_D_FF](./AIWS_D_FF.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock AIWS_D_FF realisiert ein data latch (D)-Flipflop, das einen eingehenden Datenwert speichert und bei einem Ereignis an den Ausgang weitergibt. Die Kommunikation erfolgt ausschließlich über Adapter, sodass der Baustein nahtlos in modulare Systeme integriert werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| I.E1 | Ereignis (über Adapter) | Ereignis, das das Übernehmen des Datenwertes auslöst |

### **Ereignis-Ausgänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| Q.E1 | Ereignis (über Adapter) | Ereignis, das den gespeicherten Datenwert anzeigt |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| I.D1 | ANY (über Adapter) | Datenwert, der beim Eintreffen von I.E1 übernommen wird |

### **Daten-Ausgänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| Q.D1 | ANY (über Adapter) | Gespeicherter Datenwert, der mit Q.E1 ausgegeben wird |

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| **I** | `adapter::types::unidirectional::AIWS` | Socket (Eingang) | Liefert den zu latchenden Wert sowie das auslösende Ereignis |
| **Q** | `adapter::types::unidirectional::AIWS` | Plug (Ausgang) | Gibt den gespeicherten Wert mit einem Ereignis aus |

## Funktionsweise

Der AIWS_D_FF kapselt einen internen `E_D_FF_ANY`-Baustein. Der eingehende Adapter `I` liefert über `I.E1` ein Ereignis, das den am Datenport `I.D1` anliegenden Wert übernimmt. Der gespeicherte Wert wird anschließend über `Q.D1` ausgegeben, begleitet von einem Ereignis auf `Q.E1`. Somit verhält sich der Baustein wie ein klassisches getaktetes D-Flipflop, jedoch mit einer vollständig adapterbasierten Schnittstelle.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle:** Alle Ein‑ und Ausgänge sind über unidirektionale Adapter realisiert, was eine einfache Kapselung und Wiederverwendung in unterschiedlichen Kontexten ermöglicht.
- **Interner Standard‑FB:** Die Implementierung nutzt den IEC‑61499‑Standardbaustein `E_D_FF_ANY`, der eine generische und bewährte Latch‑Funktionalität bereitstellt.
- **Unidirektionaler Datenfluss:** Der Adaptertyp `AIWS` erlaubt nur eine Datenrichtung, was die Übersichtlichkeit und Fehlervermeidung in der Vernetzung verbessert.

## Zustandsübersicht

Der AIWS_D_FF besitzt keine expliziten inneren Zustände auf der obersten Ebene. Der integrierte `E_D_FF_ANY` durchläuft zwei Phasen:
1. **Warten:** Er wartet auf ein Ereignis am Clock‑Eingang.
2. **Übernahme & Ausgabe:** Bei einem Clock‑Ereignis wird der Datenwert übernommen und ein Ausgangsereignis erzeugt.

Diese Abfolge wiederholt sich bei jedem eingehenden Ereignis.

## Anwendungsszenarien

- **Datensynchronisation:** Puffern eines Sensorsignals, das erst bei einem bestimmten Triggerereignis weitergegeben werden soll.
- **Steuerungslogik:** Speichern eines Stellsignals in Abhängigkeit eines Takts, z. B. für zeitlich abgestimmte Aktorsteuerungen.
- **Modulare Systeme:** Einbinden in Adapter‑basierte Architekturen, bei denen Funktionsblöcke über standardisierte Schnittstellen verbunden werden.

## Vergleich mit ähnlichen Bausteinen

- **Einfaches D‑Flipflop (z. B. `E_D_FF`):** Besitzt separate Ereignis‑ und Datenports, während der AIWS_D_FF die gleiche Logik über Adapter kapselt.
- **SR‑Flipflop:** Speichert zwei Zustände (Set/Reset), wohingegen der AIWS_D_FF nur einen einzigen Datenwert übernimmt und keine Rücksetzfunktion bietet.
- **Registerbausteine:** Können mehrere Bits parallel speichern, während AIWS_D_FF auf einen einzelnen Datenwert (ANY) ausgelegt ist.

## Fazit

Der AIWS_D_FF ist ein kompakter und modularer Funktionsblock zur Realisierung eines D‑Flipflops in IEC‑61499‑Systemen. Durch die ausschließliche Nutzung von Adaptern wird eine hohe Flexibilität und Wiederverwendbarkeit erreicht. Er eignet sich besonders für Anwendungen, die eine entkoppelte, ereignisgesteuerte Datenübernahme erfordern.