# AR_D_FF_TMIN


![AR_D_FF_TMIN](./AR_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Baustein **AR_D_FF_TMIN** realisiert ein Data-Latch (D-Flipflop) mit einem Eingangs‑ und einem Ausgangsadapter. Er zeichnet sich durch die optionale Vorgabe einer Mindestzeit (`Tmin`) zwischen aufeinanderfolgenden Ereignisausgaben aus. Der Kern des Bausteins basiert auf dem Standard-FB `E_D_FF_ANY_TMIN`, der die eigentliche Flipflop-Logik sowie die Zeitsteuerung übernimmt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ   | Kommentar                        |
|------|-------|----------------------------------|
| INIT | EInit | Initialisierungsanforderung (mit Parameter `Tmin`) |

### **Ereignis-Ausgänge**
| Name  | Typ   | Kommentar                       |
|-------|-------|---------------------------------|
| INITO | EInit | Initialisierungsbestätigung     |

### **Daten-Eingänge**
| Name | Typ  | Kommentar                                  |
|------|------|--------------------------------------------|
| Tmin | TIME | Mindestverzögerung zwischen zwei EO-Ereignissen |

### **Daten-Ausgänge**
Keine eigenständigen Daten-Ausgänge; der Wert wird über den Adapter `Q` ausgegeben.

### **Adapter**
| Richtung | Name | Typ                                              | Kommentar               |
|----------|------|---------------------------------------------------|-------------------------|
| Socket   | I    | `adapter::types::unidirectional::AR`              | zu übernehmender Wert   |
| Plug     | Q    | `adapter::types::unidirectional::AR`              | gelatchter Wert         |

Der Adapter `adapter::types::unidirectional::AR` vereint ein Ereignis (`E1`) und ein Datenwort (`D1`) pro Richtung.

## Funktionsweise
Der Baustein arbeitet intern mit dem FB `E_D_FF_ANY_TMIN` zusammen:

1. **Initialisierung**: Durch ein Ereignis an `INIT` wird der Parameter `Tmin` an den internen Baustein übergeben. Danach wird `INITO` ausgegeben.
2. **Flipflop-Betrieb**: Ein Ereignis am Adaptereingang `I.E1` (Socket) wird an den **CLK**-Eingang des internen Flipflops weitergeleitet. Gleichzeitig wird der Datenwert `I.D1` an den **D**-Eingang des Flipflops übergeben.
3. **Ausgabe**: Der intern erzeugte Zustand (`Q`) und das zugehörige Ereignis (`EO`) werden – unter Einhaltung der eingestellten Mindestzeit `Tmin` – an den Adapterausgang `Q` (Plug) weitergegeben. Das Ereignis `Q.E1` und der Datenwert `Q.D1` repräsentieren den gelatchten Wert.
4. **Timing**: Der Parameter `Tmin` legt fest, wie viel Zeit zwischen zwei aufeinanderfolgenden `EO`-Ereignissen mindestens vergehen muss. Überschreitet die Frequenz der Eingangsereignisse diesen Grenzwert, wird die Ausgabe entsprechend verzögert oder blockiert.

## Technische Besonderheiten
- **Adapterbasierte Kommunikation**: Der FB verwendet ausschließlich unidirektionale AR-Adapter, was ihn für lose gekoppelte oder verteilte Systeme geeignet macht.
- **Wiederverwendung eines Standardbausteins**: Die Kernlogik wird vom IEC‑61499‑Standardbaustein `E_D_FF_ANY_TMIN` bereitgestellt – somit ist die Funktionalität normkonform und erweiterbar.
- **Konfigurierbare Sperrzeit**: Die Mindestzeit `Tmin` wird zur Initialisierung übergeben und kann während der Laufzeit nicht geändert werden (nur über einen erneuten INIT‑Zyklus).

## Zustandsübersicht
Der FB selbst besitzt kein eigenes Zustandsdiagramm. Das Verhalten wird vollständig durch den eingebetteten Standardbaustein `E_D_FF_ANY_TMIN` bestimmt. Dieser befindet sich nach der INIT‑Phase im Wartezustand und wechselt bei jedem CLK‑Ereignis in einen Ausgabezustand, sofern die `Tmin`‑Zeit abgelaufen ist.

## Anwendungsszenarien
- **Entprellung von Signalen**: Wenn ein Sensorsignal (z. B. über `I`) nur mit einer Mindestpause weitergegeben werden soll, um Preller oder Rauschen zu unterdrücken.
- **Begrenzung der Ereignisrate**: In Regelungs- oder Überwachungssystemen, bei denen nachgeschaltete Komponenten nicht schneller als mit einer definierten Rate bedient werden dürfen.
- **Sichere Übergabe von Daten**: Der gelatchte Wert steht stabil zur Verfügung, bis das nächste CLK-Ereignis (am Adaptereingang) eintrifft.

## Vergleich mit ähnlichen Bausteinen
- **AR_D_FF** (ohne TMIN): Ein reiner D‑Flipflop‑Baustein ohne zeitliche Beschränkung der Ausgabeereignisse. Er eignet sich für Echtzeitanwendungen ohne Verzögerungsanforderung.
- **AR_D_FF_TMIN**: Erweitert den Basisbaustein um die Möglichkeit, die Ereignisrate zu begrenzen, was in industriellen Steuerungen mit Zeitauflagen häufig erforderlich ist.
- **AR_SR_FF**: Setzt Set‑Reset‑Logik um – im Gegensatz zum hier realisierten D‑Flipflop ist der Ausgang nicht taktgesteuert.

## Fazit
Der `AR_D_FF_TMIN` ist ein funktional erweiterter D‑Flipflop‑Baustein, der die Latch-Funktionalität mit einer konfigurierbaren Mindestzeit zwischen Ausgabeereignissen kombiniert. Seine adapterbasierte Schnittstelle und die Nutzung eines standardisierten Kerns machen ihn zu einer flexiblen und normkonformen Komponente für zeitkritische Steuerungsanwendungen im IEC‑61499‑Umfeld.