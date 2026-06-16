# ALI_D_FF


![ALI_D_FF](./ALI_D_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_D_FF** realisiert ein taktgesteuertes D-Flip-Flop (Data Latch) über Adapter-Schnittstellen. Er speichert einen Datenwert bei einer steigenden Flanke eines Taktsignals und gibt diesen bis zur nächsten Taktflanke aus. Der Baustein eignet sich für synchrone Datenspeicherung in ereignisgesteuerten Automatisierungsumgebungen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **I.E1** (über Adapter I): Takteingang – bei einer steigenden Flanke wird das Datum übernommen.

### **Ereignis-Ausgänge**
- **Q.E1** (über Adapter Q): Bestätigung der Datenübernahme – wird nach erfolgreicher Flankenerkennung und Wertzuweisung ausgegeben.

### **Daten-Eingänge**
- **I.D1** (über Adapter I): Dateneingang – der zu speichernde Wert (beliebiger Datentyp, abhängig vom Adaptertyp `ALI`).

### **Daten-Ausgänge**
- **Q.D1** (über Adapter Q): Datenausgang – der aktuell gespeicherte (gelatchte) Wert.

### **Adapter**

| Bezeichnung | Typ                          | Richtung | Beschreibung                       |
|-------------|------------------------------|----------|------------------------------------|
| I           | `adapter::types::unidirectional::ALI` | Socket   | Bietet Ereignis- und Dateneingang. |
| Q           | `adapter::types::unidirectional::ALI` | Plug     | Bietet Ereignis- und Datenausgang. |

## Funktionsweise
Der Baustein verwendet intern die Standard-Funktion `E_D_FF_ANY` aus der IEC 61499 Bibliothek.  
- Bei einer steigenden Flanke am Ereigniseingang **I.E1** wird der aktuelle Wert von **I.D1** in den internen Zustand übernommen.  
- Anschließend wird am Ausgang **Q.E1** ein Ereignis erzeugt, das signalisiert, dass der neue Wert an **Q.D1** anliegt.  
- Der Datenausgang **Q.D1** hält den gespeicherten Wert so lange, bis eine neue steigende Flanke auftritt.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle**: Der FB besitzt keine direkten Ereignis-/Dateneingänge, sondern nutzt zwei Adapter (`I` und `Q`). Dies ermöglicht eine flexible Kapselung der Verbindungen und erleichtert die Wiederverwendung in komplexen Netzwerken.
- **Interne Umsetzung**: Der Kern des Bausteins ist der FB `E_D_FF_ANY`, der typunabhängig arbeitet. Der Datentyp wird durch die verwendeten Adapter bestimmt.
- **Ereignisgesteuert**: Die Zustandsänderung erfolgt ausschließlich bei Ereignissen, was die Integration in ereignisgesteuerte Abläufe erlaubt.

## Zustandsübersicht
Der FB kennt zwei logische Zustände:
- **Zustand 0**: Ausgang `Q.D1` enthält den zuletzt gelatchten Wert, der z. B. logisch 0 sein kann.
- **Zustand 1**: Ausgang `Q.D1` enthält einen gültigen Wert ungleich 0 (sofern der Datentyp dies zulässt).

Ein Zustandswechsel erfolgt nur bei einer steigenden Flanke auf `I.E1`. Ohne Takt bleibt der Ausgang stabil.

## Anwendungsszenarien
- **Datensynchronisation**: Puffern eines Sensorsignals bis zum nächsten Takt einer Steuerung.
- **Zustandsspeicher**: Halten eines Schaltzustands in Sequenzsteuerungen.
- **Rückkopplungsfreie Verzögerung**: Zwischenspeichern von Werten in Datenpfaden, um asynchrone Nebenläufigkeiten zu vermeiden.

## Vergleich mit ähnlichen Bausteinen
- **ALI_D_FF vs. einfacher D-FF (z. B. `E_D_FF_ANY`)**: Der ALI_D_FF kapselt Ereignis- und Datenverbindungen in Adaptern und ist dadurch modularer und leichter in vordefinierte Schnittstellen einbindbar.
- **ALI_D_FF vs. RS-Flip-Flop**: Ein RS-FF erlaubt Setzen und Rücksetzen (asynchron), während der D-FF rein taktgesteuert arbeitet und keine direkten Set-/Reset-Eingänge bietet.
- **ALI_D_FF vs. T-Flip-Flop**: Der T-FF toggelt bei jedem Takt, der D-FF übernimmt einen externen Wert.

## Fazit
Der **ALI_D_FF** bietet eine saubere, adapterbasierte Lösung für synchrone Datenspeicherung. Er kombiniert die bewährte Funktionalität eines D-Flip-Flops mit der Flexibilität von IEC 61499 Adaptern. Damit eignet er sich besonders für modulare, wiederverwendbare Automatisierungskomponenten in verteilten Systemen.