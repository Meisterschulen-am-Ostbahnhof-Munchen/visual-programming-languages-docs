# AS_TO_AB


![AS_TO_AB](./AS_TO_AB.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AS_TO_AB** ist ein Composite-FB, der einen AS-Adapter (SINT) in einen AB-Adapter (BYTE) umwandelt.  
Er dient als Brücke zwischen unterschiedlichen Adapter-Typen und ermöglicht die Konvertierung des Datentyps innerhalb einer Adapter-basierten Kommunikationskette.  
Der Baustein nutzt intern die IEC‑61131-Funktion **F_SINT_TO_BYTE** und ist als reiner Datenkonverter ohne Zustandslogik realisiert.

## Schnittstellenstruktur
Da der FB über keine direkten Ereignis- oder Datenports verfügt, werden Ein- und Ausgänge über die folgenden Adapter bereitgestellt:

### **Ereignis-Eingänge**
| Port | Beschreibung |
|------|--------------|
| `AS_IN.E1` | Startet die Konvertierung eines SINT-Werts. |

### **Ereignis-Ausgänge**
| Port | Beschreibung |
|------|--------------|
| `AB_OUT.E1` | Signalisiert den Abschluss der Konvertierung. |

### **Daten-Eingänge**
| Port | Datentyp | Beschreibung |
|------|----------|--------------|
| `AS_IN.D1` | SINT | Der zu konvertierende Wert (Signed Short Integer). |

### **Daten-Ausgänge**
| Port | Datentyp | Beschreibung |
|------|----------|--------------|
| `AB_OUT.D1` | BYTE | Der konvertierte Wert (Byte). |

### **Adapter**
| Bezeichnung | Typ | Richtung | Kommentar |
|-------------|-----|----------|-----------|
| `AS_IN` | `adapter::types::unidirectional::AS` | Socket (Eingang) | SINT Adapter Eingang |
| `AB_OUT` | `adapter::types::unidirectional::AB` | Plug (Ausgang) | BYTE Adapter Ausgang |

## Funktionsweise
1. Ein eingehendes Ereignis auf `AS_IN.E1` triggert die Verarbeitung.  
2. Der aktuelle Wert von `AS_IN.D1` (SINT) wird ausgelesen.  
3. Die interne Instanz `F_SINT_TO_BYTE` führt die Umwandlung in einen BYTE-Wert durch.  
4. Nach erfolgreicher Konvertierung wird ein Ereignis auf `AB_OUT.E1` ausgegeben und der berechnete BYTE-Wert auf `AB_OUT.D1` bereitgestellt.  

Die Konvertierung erfolgt streng nach IEC‑61131-Semantik: Der SINT-Wert wird bitweise auf den BYTE-Datentyp abgebildet, ohne Vorzeichen- oder Bereichsfragen (da SINT 8 Bit umfasst, identisch zu BYTE).

## Technische Besonderheiten
- **Composite-FB**: Der Baustein kapselt die Konvertierungslogik und stellt sie als Adapter-Konverter bereit.  
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangs-Adapter sind unidirektional ausgelegt – Daten fließen nur in eine Richtung.  
- **Kein interner Zustand**: Der FB verhält sich wie eine reine Funktion; jede Aktivierung erzeugt unabhängig vom vorherigen Zustand das korrekte Ergebnis.  
- **Abhängigkeit**: Der Baustein importiert die IEC‑61131-Funktion `F_SINT_TO_BYTE`, die in der Zielumgebung verfügbar sein muss.  

## Zustandsübersicht
Der FB besitzt **kein eigenes Zustandsdiagramm** – er ist ereignisgesteuert und führt bei jeder Aktivierung sofort eine einmalige Konvertierung aus.  
Das interne Element `F_SINT_TO_BYTE` ist ebenfalls zustandslos.

## Anwendungsszenarien
- **Adapter-Kopplung**: Wenn ein Sensor oder Aktor einen AS-Adapter (SINT) bereitstellt, das nachfolgende System aber einen AB-Adapter (BYTE) erwartet, wird dieser FB als Zwischenstück eingesetzt.  
- **Protokollanpassung**: In SPS- oder Automatisierungssystemen müssen häufig unterschiedliche Datentypen zwischen Adaptern konvertiert werden – hier speziell SINT ↔ BYTE.  
- **Modularisierung**: Der FB erlaubt es, Konvertierungslogik in wiederverwendbaren Adapter-Bausteinen zu kapseln, anstatt sie in jedem Anwendungs-FB neu zu implementieren.

## Vergleich mit ähnlichen Bausteinen
- **AS_TO_WORD / AS_TO_INT**: Konvertieren SINT in WORD oder INT; AS_TO_AB ist auf BYTE spezialisiert.  
- **Direkte Verwendung von `F_SINT_TO_BYTE`**: Der Composite-FB bietet den Vorteil, dass die Konvertierung über Adapter-Ports erfolgt, was keine manuelle Verschaltung der Ereignis- und Datenflüsse benötigt.  
- **Andere Adapter-Konverter**: Falls in der Bibliothek ähnliche Adapter-Konverter existieren (z.B. `AB_TO_AS`), ergänzt dieser FB die unidirektionale Konvertierung in die Gegenrichtung.

## Fazit
Der **AS_TO_AB**-Funktionsblock ist ein einfacher, aber nützlicher Konverter für Adapter-basierte Architekturen.  
Er erlaubt die nahtlose Integration von SINT- und BYTE-kommunizierenden Komponenten, ohne dass der Anwender die zugrundeliegende Konvertierung selbst programmieren muss.  
Dank seiner Composite-Struktur bleibt die Logik klar und wartbar – ideal für den Einsatz in industriellen Steuerungssystemen nach IEC 61499.