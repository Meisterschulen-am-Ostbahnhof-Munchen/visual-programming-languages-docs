# AL_D_FF_TMIN


![AL_D_FF_TMIN](./AL_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AL_D_FF_TMIN implementiert ein flankengesteuertes D‑Flip‑Flop (Data Latch) mit einer einstellbaren minimalen Verweilzeit zwischen den Ausgangsereignissen (Minimum inter‑disposal time). Er übernimmt einen Datenwert bei einem eingehenden Ereignis, speichert diesen und gibt ihn – zusammen mit einem eigenen Ereignis – erst nach Ablauf der vorgegebenen Mindestzeit wieder aus. So wird eine Begrenzung der Ausgabeereignisrate erreicht.

## Schnittstellenstruktur
### **Ereignis‑Eingänge**
- **INIT**: Initialisierungsanforderung; legt den Parameter Tmin für die Mindestzeit zwischen Ausgangsereignissen fest.

### **Ereignis‑Ausgänge**
- **INITO**: Bestätigung der durchgeführten Initialisierung.

### **Daten‑Eingänge**
- **Tmin** (TIME): Minimaler zeitlicher Abstand, der zwischen zwei aufeinanderfolgenden Ausgangsereignissen (EO) eingehalten werden muss.

### **Daten‑Ausgänge**
- Keine direkten Datenausgänge – die gelatchten Werte werden ausschließlich über den Ausgangs‑Adapter Q übertragen.

### **Adapter**
- **I** (Socket, Typ: `adapter::types::unidirectional::AL`): Eingangs‑Adapter für den zu latchierenden Wert. Über die Ereignisschnittstelle (E1) wird der Latch‑Impuls empfangen, über die Datenschnittstelle (D1) der zu übernehmende Datenwert bereitgestellt.
- **Q** (Plug, Typ: `adapter::types::unidirectional::AL`): Ausgangs‑Adapter für den gespeicherten Wert. Bei jedem erfolgreichen Latch‑Vorgang wird ein Ereignis (E1) gesendet und der aktuell gespeicherte Datenwert (D1) ausgegeben.

## Funktionsweise
Der Baustein nutzt intern den vordefinierten Flip‑Flop‑Baustein `E_D_FF_ANY_TMIN`.  
Sobald ein Ereignis am Eingangs‑Adapter (I.E1) eintrifft, wird der gleichzeitig anliegende Datenwert (I.D1) übernommen und intern gespeichert. Das Ausgangsereignis (Q.E1) wird jedoch erst dann erzeugt, wenn seit dem letzten Ausgangsereignis mindestens die mit Tmin festgelegte Zeitspanne vergangen ist. Erst dann wird der gespeicherte Wert an den Ausgangs‑Adapter (Q.D1) weitergegeben. Die Initialisierung mit INIT setzt den Parameter Tmin und muss vor dem ersten Gebrauch erfolgen.

## Technische Besonderheiten
- **Mindestzeit zwischen Ausgangsereignissen**: Die Verzögerung Tmin begrenzt die Frequenz der Ausgangsereignisse – nützlich zur Vermeidung von Busüberlastungen oder zur Begrenzung der Aktor‑Ansteuerungsrate.
- **Adapter‑Schnittstellen**: Die Kopplung erfolgt über standardisierte, unidirektionale Adapter (`adapter::types::unidirectional::AL`). Dadurch ist der Baustein flexibel in verschiedene Applikationen integrierbar.
- **Flankengetriggert**: Der interne Flip‑Flop reagiert auf die steigende Flanke des Ereignisses am Eingangs‑Adapter (I.E1).

## Zustandsübersicht
Der Baustein besitzt keinen explizit dargestellten Zustandsautomaten. Sein Verhalten ergibt sich aus dem internen D‑Flip‑Flop mit Zeitsteuerung:
- Nach erfolgreicher Initialisierung (INIT → INITO) wartet der Baustein auf ein Ereignis am Eingangs‑Adapter I.
- Bei einem Ereignis wird der anliegende Datenwert gelatcht. Sofort danach wird geprüft, ob die seit dem letzten Ausgangsereignis vergangene Zeit bereits Tmin überschreitet.
  - Falls ja: Das Ausgangsereignis wird sofort erzeugt.
  - Falls nein: Der Ausgang wird solange blockiert, bis die Wartezeit abgelaufen ist; danach erfolgt die Ausgabe.
- Während der Wartezeit eingehende Ereignisse werden (je nach interner Implementierung des zugrunde liegenden Bausteins) möglicherweise ignoriert oder zwischengespeichert – in der Regel wird nur der aktuellste Datenwert für die nächste Ausgabe berücksichtigt.

## Anwendungsszenarien
- **Synchronisation zeitkritischer Steuerungen**, bei denen Daten nicht häufiger als in einem vorgegebenen Rhythmus aktualisiert werden dürfen.
- **Entprellung von Signalen** oder Drosselung von Ereignisketten in Kommunikationsnetzwerken.
- **Einfache Zustandsmaschinen**, die auf äußere Ereignisse reagieren und eine minimale Reaktionszeit einhalten müssen (z. B. in der Automatisierungstechnik oder Steuerung physikalischer Aktoren).

## Vergleich mit ähnlichen Bausteinen
- **AL_D_FF**: Ein einfaches D‑Flip‑Flop ohne Mindestzeit zwischen Ausgangsereignissen – AL_D_FF_TMIN erweitert dieses um die Tmin‑Steuerung und die Adapter‑Schnittstellen.
- **E_D_FF_ANY_TMIN**: Der zugrunde liegende, generische Flip‑Flop, der direkt (ohne Adapter‑Kapselung) verwendet werden kann. AL_D_FF_TMIN kapselt diesen in ein plug‑and‑play‑fähiges Adapter‑Format.
- **R_TRIG / F_TRIG**: Erkennen steigende bzw. fallende Flanken, speichern aber keine Datenwerte und bieten keine einstellbare Ausgabe‑Verzögerung.

## Fazit
Der Funktionsblock AL_D_FF_TMIN bietet eine zuverlässige, flankengesteuerte D‑Latch‑Funktion mit einer einstellbaren Mindestzeit zwischen Ausgangsereignissen. Durch die Verwendung standardisierter Adapter‑Schnittstellen ist er einfach in IEC‑61499‑Applikationen integrierbar und eignet sich besonders für Anwendungen, die eine Begrenzung der Ereignisrate oder eine zeitlich gesteuerte Datenfreigabe erfordern.