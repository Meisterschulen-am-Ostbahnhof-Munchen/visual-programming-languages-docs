# AUDI_D_FF_TMIN


![AUDI_D_FF_TMIN](./AUDI_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUDI_D_FF_TMIN** realisiert ein D‑Flipflop (Data Latch) mit einer minimalen Sperrzeit zwischen aufeinanderfolgenden Ausgangsereignissen. Er dient dazu, einen über einen Adapter eingehenden Wert zu übernehmen und über einen zweiten Adapter auszugeben, wobei die Weitergabe des Ausgangsereignisses zeitlich gesteuert wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ   | Beschreibung                                |
|-------|-------|---------------------------------------------|
| INIT  | EInit | Initialisierung des Bausteins; setzt die minimale Zeit zwischen zwei EO-Ereignissen. |

### **Ereignis-Ausgänge**

| Name  | Typ   | Beschreibung                                |
|-------|-------|---------------------------------------------|
| INITO | EInit | Bestätigung der abgeschlossenen Initialisierung. |

### **Daten-Eingänge**

| Name | Typ  | Beschreibung                                                   |
|------|------|----------------------------------------------------------------|
| Tmin | TIME | Minimale Zeitdauer, die zwischen zwei aufeinanderfolgenden EO-Ereignissen mindestens vergehen muss. |

### **Daten-Ausgänge**

Keine direkten Datenausgänge; der gelatchte Wert wird über den Adapter **Q** bereitgestellt.

### **Adapter**

| Name | Typ (unidirektional) | Rolle                                            |
|------|----------------------|--------------------------------------------------|
| I    | AUDI                 | Eingangsadapter: liefert den zu latchnden Wert (über D1) und das Latch-Ereignis (über E1). |
| Q    | AUDI                 | Ausgangsadapter: gibt den gelatchten Wert (über D1) sowie ein Ausgangsereignis (über E1) aus. |

## Funktionsweise

Der Baustein enthält intern eine Instanz des FBs `E_D_FF_ANY_TMIN`, der die Kernlogik eines D‑Flipflops mit zeitlicher Begrenzung realisiert.

1. **Initialisierung**  
   Ein INIT-Ereignis setzt die minimale Verzögerungszeit `Tmin` (über die With‑Assoziation) und wird an die interne Instanz weitergeleitet. Nach erfolgreicher Initialisierung wird INITO ausgegeben.

2. **Latch‑Vorgang**  
   Ein Ereignis am Eingang `I.E1` (des Adapters) wird als Takt (CLK) an das interne Flipflop übergeben. Gleichzeitig wird der Wert von `I.D1` (D‑Eingang) übernommen. Der gelatchte Wert erscheint am Ausgang `Q.D1`, das entsprechende Ausgangsereignis am Ereignisausgang des Adapters (`Q.E1`).

3. **Minimale Wartezeit**  
   Der interne FB erzwingt eine zeitliche Mindestdistanz zwischen aufeinanderfolgenden `Q.E1`-Ereignissen. Überschreitet die an `Tmin` definierte Zeit, wird das nächste Ausgangsereignis erst nach Ablauf dieser Zeitspanne ausgelöst. Auf diese Weise lassen sich Überlastungen auf der Ausgangsseite vermeiden.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation**  
  Der Baustein verwendet zwei unidirektionale AUDI‑Adapter für Ein‑ und Ausgang. Dadurch wird eine lose Kopplung zwischen Datenfluss und Ereignissteuerung erreicht.

- **Intervallsteuerung**  
  Die minimale Zeit zwischen zwei EO-Ereignissen wird über den Parameter `Tmin` konfiguriert. Der interne FB `E_D_FF_ANY_TMIN` stellt sicher, dass diese Bedingung eingehalten wird, indem er eingehende Taktereignisse bei Bedarf verzögert.

- **Keine expliziten Datenausgänge**  
  Der gelatchte Wert wird ausschließlich über den Adapter `Q` zur Verfügung gestellt. Dies vereinfacht die Verbindung zu nachfolgenden Bausteinen mit gleichem Adaptertyp.

## Zustandsübersicht

Der FB besitzt keine nach außen sichtbaren Zustände, da die Zustandslogik im inneren FB gekapselt ist. Die interne Logik durchläuft mindestens die folgenden internen Zustände:

- **IDLE**: Warten auf INIT oder auf ein Taktereignis (I.E1).
- **LATCH**: Wert wird gespeichert; Wartezeit prüfen.
- **OUTPUT**: Ausgabe von Q.E1 und Q.D1, wenn die Mindestzeit seit dem letzten Ausgangsereignis abgelaufen ist.

Ein INIT‑Ereignis setzt alle Zustände zurück.

## Anwendungsszenarien

- **Datenpuffer mit Zeitsteuerung**  
  Übernahme von Messwerten oder Steuersignalen in festen, zeitlichen Abständen, z. B. zur Entkopplung eines schnellen Sensors von einem langsamen Aktor.

- **Ereignisfilter**  
  Unterdrückung von Ereignissen, die zu schnell aufeinander folgen (Debouncing auf Anwendungsebene).

- **Synchronisation**  
  Verwendung als Basisbaustein für die Realisierung von Verzögerungsgliedern oder Taktsperren in IEC‑61499‑Anwendungen.

## Vergleich mit ähnlichen Bausteinen

| Baustein            | Besonderheit                                                      |
|---------------------|-------------------------------------------------------------------|
| **AUDI_D_FF**       | Reines D‑Flipflop ohne zeitliche Begrenzung zwischen EO-Ereignissen. |
| **E_D_FF_ANY**      | Standard‑D‑Flipflop mit universellen Datentypen, jedoch ohne minimale Wartezeit. |
| **AUDI_D_FF_TMIN**  | Wie AUDI_D_FF, aber mit zusätzlicher `Tmin`-Parameter zur Steuerung der Mindestpause zwischen Ausgangsereignissen. |

## Fazit

Der **AUDI_D_FF_TMIN** ist ein spezialisierter D‑Flipflop‑Baustein, der die Ausgabe von Ereignissen und Werten zeitlich begrenzt. Durch die Adapter‑Schnittstelle fügt er sich nahtlos in unidirektionale Kommunikationsstrukturen ein. Die Kombination aus Latch‑Funktion und einstellbarer Sperrzeit macht ihn zu einem wertvollen Werkzeug für die ereignisgesteuerte Echtzeitverarbeitung in Automatisierungssystemen.