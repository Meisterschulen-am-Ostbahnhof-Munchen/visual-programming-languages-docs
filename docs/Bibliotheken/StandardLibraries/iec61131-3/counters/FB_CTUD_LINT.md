# FB_CTUD_LINT

```{index} single: FB_CTUD_LINT
```

<img width="1418" height="340" alt="FB_CTUD_LINT" src="https://github.com/user-attachments/assets/3ef801dc-5210-49fd-b0d4-4c34251fea5f" />

* * * * * * * * * *
## Einleitung
Der FB_CTUD_LINT ist ein Funktionsblock für einen hoch- und runterzählenden Zähler mit 64-Bit-Ganzzahlwerten (LINT). Er bietet Funktionen zum Zählen nach oben und unten, zum Zurücksetzen des Zählers sowie zum Laden eines vordefinierten Wertes. Der Zähler ist besonders für Anwendungen geeignet, die große Zahlenbereiche erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Wird verwendet, um den Zählvorgang zu starten. Verknüpft mit den Daten-Eingängen CU, CD, R, LD und PV.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach Abschluss der Zähloperation ausgegeben. Verknüpft mit den Daten-Ausgängen QU, QD und CV.

### **Daten-Eingänge**
- **CU (BOOL)**: Signal zum Hochzählen (Count Up).
- **CD (BOOL)**: Signal zum Runterzählen (Count Down).
- **R (BOOL)**: Signal zum Zurücksetzen des Zählers (Reset).
- **LD (BOOL)**: Signal zum Laden des vordefinierten Wertes (Load).
- **PV (LINT)**: Vordefinierter Wert (Preset Value), der geladen wird, wenn LD aktiv ist.

### **Daten-Ausgänge**
- **QU (BOOL)**: Signal, das anzeigt, ob der Zählerstand größer oder gleich dem vordefinierten Wert ist.
- **QD (BOOL)**: Signal, das anzeigt, ob der Zählerstand kleiner oder gleich 0 ist.
- **CV (LINT)**: Aktueller Zählerstand (Count Value).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt folgende Operationen aus, wenn das REQ-Ereignis eintritt:
1. **Reset (R)**: Setzt den Zählerstand (CV) auf 0 zurück.
2. **Load (LD)**: Lädt den vordefinierten Wert (PV) in den Zählerstand (CV).
3. **Count Up (CU)**: Erhöht den Zählerstand um 1, solange der maximale Wert (9223372036854775807) nicht überschritten wird.
4. **Count Down (CD)**: Verringert den Zählerstand um 1, solange der minimale Wert (-9223372036854775808) nicht unterschritten wird.
5. **Ausgänge QU und QD**: Werden basierend auf dem aktuellen Zählerstand aktualisiert.

## Technische Besonderheiten
- Verwendet 64-Bit-Ganzzahlen (LINT) für den Zählerstand und den vordefinierten Wert.
- Unterstützt sowohl Hoch- als auch Runterzählen mit Überlauf- und Unterlaufschutz.
- Keine gleichzeitige Aktivierung von CU und CD möglich (verhindert Konflikte).

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand außer dem aktuellen Zählerstand (CV). Die Logik wird bei jedem REQ-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Industrielle Steuerungen mit großen Zählbereichen.
- Überwachung von Produktionsprozessen.
- Zeitmessung oder Ereigniszählung in langen Zeiträumen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Zählern bietet FB_CTUD_LINT eine größere Zahlenreichweite (64-Bit).
- Ähnlich zu FB_CTUD, aber mit LINT-Datentyp für erweiterte Anwendungen.

## Fazit
Der FB_CTUD_LINT ist ein leistungsstarker Zähler für Anwendungen, die große Zahlenbereiche erfordern. Seine Flexibilität und Robustheit machen ihn ideal für industrielle Steuerungen und komplexe Zählaufgaben.
