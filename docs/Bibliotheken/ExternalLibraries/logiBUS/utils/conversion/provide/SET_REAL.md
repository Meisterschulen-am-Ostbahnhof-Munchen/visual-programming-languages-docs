# SET_REAL


![SET_REAL](./SET_REAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_REAL** dient dazu, einen REAL-Wert von einem Dateneingang auf eine InOut-Variable zu schreiben. Er ist ein einfacher, ereignisgesteuerter Baustein, der nach einer Anforderung (REQ) den aktuellen Eingangswert IN an die referenzierte Variable OUT weitergibt und den Vorgang durch ein Bestätigungsereignis (CNF) quittiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| REQ  | Event | Normale Ausführungsanforderung (mit IN und OUT verbunden) |

### **Ereignis-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| CNF  | Event | Bestätigung der Ausführung (mit OUT verbunden) |

### **Daten-Eingänge**
| Name | Typ | Initialwert | Beschreibung |
|------|-----|-------------|--------------|
| IN   | REAL | 0.0 | Wert, der geschrieben werden soll |
| OUT  | REAL (InOut) | 0.0 | Zielvariable (InOut – lesend und schreibend) |

### **Daten-Ausgänge**
Keine separaten Datenausgänge vorhanden. Der InOut-Parameter OUT fungiert gleichzeitig als Ausgang und wird nach der Zuweisung aktualisiert.

### **Adapter**
Keine.

## Funktionsweise
Der FB besitzt einen einzigen Ausführungszustand **REQ**. Sobald ein Ereignis am Eingang **REQ** eintrifft, wird der hinterlegte Algorithmus ausgeführt:

```
OUT := IN;
```

Der aktuelle Wert von IN wird der InOut-Variable OUT zugewiesen. Anschließend wird das Ereignis **CNF** ausgegeben, um den Abschluss der Operation zu signalisieren. Der Vorgang ist atomar und benötigt keine weiteren Zustandsübergänge.

## Technische Besonderheiten
- **InOut-Parameter OUT**: Die Variable OUT ist sowohl lesbar als auch beschreibbar. Sie wird direkt von der aufrufenden Umgebung referenziert, sodass die Zuweisung unmittelbar den Wert an der Ursprungsadresse ändert.
- **Initialwerte**: Sowohl IN als auch OUT sind mit 0.0 initialisiert. Dies verhindert undefinierte Zustände vor der ersten Ausführung.
- **Einfachheit**: Der FB besteht aus nur einem Zustand und einem Algorithmus, was eine sehr geringe Laufzeitkomplexität garantiert.

## Zustandsübersicht
| Zustand | Beschreibung | Aktion | Ausgabe |
|---------|--------------|--------|---------|
| REQ     | Warte auf Ausführungsanforderung | Führe Algorithmus REQ aus → OUT := IN | CNF |

Es existiert kein weiterer Zustand; der FB kehrt nach dem Durchlauf sofort wieder in den wartenden Zustand REQ zurück.

## Anwendungsszenarien
- **Parametereinstellung**: Übergabe eines REAL-Werts an eine globale Konfigurationsvariable, z. B. zur Skalierung oder für Sollwerte.
- **Initialisierung**: Setzen einer InOut-Variable auf einen definierten Startwert während der Inbetriebnahme.
- **Wertkopie innerhalb einer Applikation**: Einfaches Überschreiben einer bestehenden REAL-Variablen durch einen anderen Wert, gesteuert durch ein Ereignis.

## Vergleich mit ähnlichen Bausteinen
| FB | Typ | Unterschied |
|----|-----|-------------|
| **SET_BOOL** | BOOL | Schreibt boolesche Werte, analoge Funktionsweise |
| **SET_INT** | INT | Schreibt Ganzzahlen, identische Ereignissteuerung |
| **MOVE** (generisch) | ANY | Kann beliebige Datentypen kopieren, erfordert jedoch Typanpassung und hat oft mehrere Zustände |
| **SET_REAL** | REAL | Speziell für REAL optimiert, minimale Zustände und klare Semantik |

Im Vergleich zu einem generischen MOVE-Baustein bietet SET_REAL eine schlankere Implementierung und ist auf den häufig benötigten REAL-Typ zugeschnitten.

## Fazit
Der Funktionsblock **SET_REAL** ist ein einfacher, aber effektiver Baustein zum gezielten Setzen einer REAL-Variablen. Dank seiner minimalen Zustandsmaschine und der direkten Verwendung von InOut-Parametern eignet er sich hervorragend für ereignisgesteuerte Zuweisungen in IEC 61499-Applikationen. Er reduziert Komplexität und erhöht die Lesbarkeit des Steuerungscodes.