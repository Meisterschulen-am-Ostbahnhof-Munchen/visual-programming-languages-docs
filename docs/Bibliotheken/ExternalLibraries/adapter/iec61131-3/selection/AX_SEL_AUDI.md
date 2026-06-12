# AX_SEL_AUDI


![AX_SEL_AUDI](./AX_SEL_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_SEL_AUDI** realisiert eine binäre Auswahlfunktion nach IEC 61131-3. Er wählt aus zwei Eingangswerten (IN0, IN1) einen aus und gibt diesen über einen Adapter-Ausgang weiter. Die Steuerung der Selektion erfolgt über einen Adapter-Eingang, der ein Ereignis und ein Auswahlsignal bereitstellt. Der Baustein ist für modulare, adapterbasierte Architekturen ausgelegt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Kommentar |
|----------|-----------|
| **EI0** | Setzt den Eingang IN0 (mit IN0 verbunden). Das Ereignis dient der Aktualisierung des Wertes IN0. |
| **EI1** | Setzt den Eingang IN1 (mit IN1 verbunden). Das Ereignis dient der Aktualisierung des Wertes IN1. |

### **Ereignis-Ausgänge**
Der Baustein besitzt keine expliziten Ereignis-Ausgänge. Die Ausgabe von Ereignissen erfolgt ausschließlich über den **OUT**-Adapter (siehe Adapter).

### **Daten-Eingänge**
| Variable | Typ   | Kommentar                         |
|----------|-------|-----------------------------------|
| **IN0**  | UDINT | Erster selektierbarer Eingangswert. |
| **IN1**  | UDINT | Zweiter selektierbarer Eingangswert. |

### **Daten-Ausgänge**
Der Baustein besitzt keine expliziten Daten-Ausgänge. Der ausgewählte Wert wird über den **OUT**-Adapter ausgegeben (siehe Adapter).

### **Adapter**
| Adapter | Richtung | Typ (Paket) | Kommentar |
|---------|----------|-------------|-----------|
| **G**   | Socket   | `adapter::types::unidirectional::AX` | Liefert das Steuersignal zur Auswahl: Ereignis **E1** und Datenwert **D1** (z. B. BOOL, 0 = IN0, 1 = IN1). |
| **OUT** | Plug     | `adapter::types::unidirectional::AUDI` | Gibt das Ergebnis der Selektion aus: Ereignis **E1** und Datenwert **D1** (UDINT). |

## Funktionsweise

1. **Eingangswerte setzen:** Über die Ereignisse **EI0** bzw. **EI1** werden die aktuellen Werte von **IN0** und **IN1** im internen Kontext gespeichert (die Ereignisse sind mit den jeweiligen Daten assoziiert).
2. **Selektion triggern:** Ein Ereignis auf **G.E1** löst die Auswahl aus. Der interne Funktionsblock **F_SEL** (IEC 61131-3 `SELECTION`) wertet das Steuersignal **G.D1** aus.
   - Ist **G.D1 = 0**, wird **IN0** ausgewählt.
   - Ist **G.D1 = 1**, wird **IN1** ausgewählt.
3. **Ausgabe:** Der selektierte Wert wird über **OUT.D1** ausgegeben. Gleichzeitig wird ein Ereignis auf **OUT.E1** erzeugt, um nachgeschaltete Bausteine zu informieren.

Das folgende interne Netzwerk fasst die Funktionsweise zusammen:

```
G.E1 ──► F_SEL.REQ
F_SEL.CNF ──► OUT.E1

G.D1 ──► F_SEL.G
IN0  ──► F_SEL.IN0
IN1  ──► F_SEL.IN1
F_SEL.OUT ──► OUT.D1
```

## Technische Besonderheiten
- **Adapterbasierte Ein‑/Ausgabe:** Statt klassischer Ein‑/Ausgangsvariablen werden Adapter (Plug/Socket) verwendet. Dies ermöglicht eine lose Kopplung und Wiederverwendung in verschiedenen Umgebungen.
- **Interner IEC‑Baustein:** Die Kernlogik (F_SEL) ist ein standardisierter Funktionsblock nach IEC 61131-3. AX_SEL_AUDI kapselt diesen und ergänzt Adapterschnittstellen.
- **Versionierung:** Der Baustein liegt in Version 3.0 vor, ursprünglich entwickelt von der TU Wien (2012) und später aktualisiert.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten. Die Abläufe sind rein ereignisgesteuert:

- **Warten:** Der FB wartet auf ein Ereignis auf **G.E1**.
- **Selektion:** Bei Empfang von G.E1 wird sofort die Auswahl durchgeführt und das Ergebnis auf OUT ausgegeben.
- **Aktualisierung:** Die Ereignisse EI0 und EI1 können jederzeit die Eingangswerte neu setzen, wirken sich aber erst bei der nächsten Selektion aus.

## Anwendungsszenarien
- **Signalumschaltung:** Auswahl zwischen zwei Sensorsignalen (z. B. Temperatur‑/Druckwerte) basierend auf einem Steuersignal (z. B. Betriebsart).
- **Moduswechsel:** Umschalten zwischen verschiedenen Regelparametern oder Sollwerten in einer Steuerung.
- **Redundanz:** Falls ein Signal ausfällt, kann über das Steuersignal auf ein alternatives Signal umgeschaltet werden.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Eigenschaften |
|----------|---------------|
| **F_SEL** (Standard) | Reine Funktionsblock‑Implementierung ohne Adapter; verwendet klassische Ein‑/Ausgangsvariablen. |
| **AX_SEL_AUDI** | Kapselt F_SEL und fügt Adapterschnittstellen hinzu; geeignet für adapterbasierte Architekturen. |
| **MUX‑Bausteine** | Mehrkanalige Auswahl (z. B. 4‑zu‑1), oft mit zusätzlichem Index‑Eingang. AX_SEL_AUDI ist auf zwei Kanäle begrenzt. |

## Fazit
**AX_SEL_AUDI** ist ein kompakter, adaptergestützter Funktionsblock zur binären Signalauswahl. Er vereinfacht den Einsatz in modularen Steuerungsarchitekturen, indem er die Standard‑Selektionslogik mit modernen Adapterschnittstellen kombiniert. Die klare Ereignissteuerung und die einfache Funktionsweise machen ihn zu einer robusten Lösung für typische Umschalt- und Selektionsaufgaben in der Automatisierungstechnik.