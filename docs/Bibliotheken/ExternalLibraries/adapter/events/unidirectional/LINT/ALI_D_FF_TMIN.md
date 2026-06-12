# ALI_D_FF_TMIN


![ALI_D_FF_TMIN](./ALI_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_D_FF_TMIN** realisiert einen Datenspeicher (D-Flip-Flop) mit einem Adapter-gestützten Ein- und Ausgang und einer konfigurierbaren Mindestverweilzeit zwischen den Ausgangsereignissen. Er dient dazu, einen anliegenden Datenwert bei einer steigenden Flanke am Eingang zu übernehmen und nach Ablauf einer minimalen Zeit freizugeben, um zyklische Bedingungen oder Zeitauflösungsprobleme in der Kommunikation zu vermeiden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Mit Variablen | Kommentar |
|----------|-----|---------------|-----------|
| INIT     | EInit | Tmin | Initialisierungsanforderung, setzt die minimale Haltezeit |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Mit Variablen | Kommentar |
|----------|-----|---------------|-----------|
| INITO    | EInit | – | Bestätigung der Initialisierung |

### **Daten-Eingänge**
| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| Tmin     | TIME  | Minimale Zeit zwischen zwei Ausgangsereignissen (EO) |

### **Daten-Ausgänge**
Keine direkten Datenausgänge. Der latched Wert wird über den **Q-Adapter** bereitgestellt.

### **Adapter**
| Bezeichnung | Typ | Richtung | Kommentar |
|-------------|-----|----------|-----------|
| I           | ALI (unidirectional) | Socket (Eingang) | Wert, der übernommen werden soll |
| Q           | ALI (unidirectional) | Plug (Ausgang)  | Gespeicherter Wert |

## Funktionsweise
Der **ALI_D_FF_TMIN** kapselt einen internen FB vom Typ `E_D_FF_ANY_TMIN`. Dessen Funktionsweise:
- Bei einem Ereignis am Eingangsadapter **I.E1** (steigende Flanke) wird der Datenwert **I.D1** übernommen.
- Das Ausgangsereignis **EO** wird jedoch erst ausgelöst, wenn seit dem letzten **EO** mindestens die Zeit **Tmin** vergangen ist.
- Die Initialisierung (INIT) setzt den internen Zeitgeber und bereitet den Baustein vor.

Der Baustein arbeitet asynchron, die Zeitsteuerung erfolgt über den internen FB.

## Technische Besonderheiten
- Die Logik ist vollständig in den internen FB `E_D_FF_ANY_TMIN` ausgelagert, der einen eigenen Zustandsautomaten und Zeitgeber besitzt.
- Die **Tmin**-Zeit wird nur einmal bei INIT gesetzt und gilt für die gesamte Lebensdauer.
- Adapter **I** (Eingang) und **Q** (Ausgang) sind unidirektional vom Typ `ALI`, sie übertragen sowohl Ereignis als auch Daten.
- Der Baustein implementiert kein eigenes Verhalten auf der obersten Ebene, sondern delegiert alle Funktionen.

## Zustandsübersicht
Da der FB intern `E_D_FF_ANY_TMIN` verwendet, besitzt er implizit folgende Zustände:
1. **Initialisiert**: Nach INIT, bereit für erste Flanke.
2. **Flanke empfangen**: Wert wurde gespeichert, EO wird nach **Tmin** gesendet.
3. **Warten auf Mindestzeit**: Kein neues EO möglich, bis Tmin abgelaufen.
4. **Bereit**: Nach Ablauf der Wartezeit kann das nächste EO ausgelöst werden.

Der genaue Zustandsautomat liegt jedoch im internen FB und ist hier nicht abgebildet.

## Anwendungsszenarien
- **Datensicherung in zeitgesteuerten Bussystemen**: Pufferung von Werten bei einem Takt, die nur in definierten Abständen weitergegeben werden dürfen.
- **Entprellung von Signalen**: Verhindert, dass schnelles Ein- und Ausschalten zu vielen Ereignissen auf der Logikebene führt.
- **Sequenzielle Verarbeitung mit Mindestabstand**: Sicherstellung, dass nachfolgende Bausteine genügend Zeit zur Verarbeitung haben.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Unterschied |
|----------|-------------|
| `ALI_D_FF` (ohne TMIN) | Keine Mindestzeit zwischen Ausgangsereignissen, sofortige Weiterleitung bei jeder Flanke. |
| `E_D_FF` (Standard-61499) | Ereignis-Ein- und Ausgänge direkt, ohne Adapter und ohne Zeitsteuerung. |
| `E_D_FF_ANY_TMIN` | Gleiche Funktionalität, aber mit eigenen Daten- und Ereignis-Ports, nicht über Adapter. |

Der **ALI_D_FF_TMIN** erweitert die Adapter-Schnittstelle um eine komfortable Kapselung und Fügt die Zeitsteuerung hinzu, die bei einfachen Flip-Flops fehlt.

## Fazit
Der **ALI_D_FF_TMIN** ist ein nützlicher Baustein für Anwendungen, die eine verzögerte oder getaktete Weitergabe von Daten über Adapter erfordern. Durch die konfigurierbare Mindestzeit zwischen den Ausgangsereignissen eignet er sich besonders für zeitkritische oder entprellte Kommunikationsstrecken. Die interne Implementierung über einen bewährten FB sorgt für Robustheit und Wiederverwendbarkeit.