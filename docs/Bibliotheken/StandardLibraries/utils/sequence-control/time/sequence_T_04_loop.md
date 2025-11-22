# sequence_T_04_loop

![sequence_T_04_loop](https://github.com/user-attachments/assets/41b2ae88-5ef2-4949-a214-3e7e46eb7da6)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_T_04_loop` implementiert eine zyklische Sequenz mit 4 Zuständen, deren Übergänge zeitgesteuert erfolgen. Entwickelt von HR Agrartechnik GmbH, dient dieser Baustein zur Steuerung von Abläufen, bei denen verschiedene Aktionen nacheinander in festgelegten Zeitintervallen ausgeführt werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `START_S1`: Startet die Sequenz von Zustand 1 (State_01). Verwendet die Zeitparameter für alle Zustandsübergänge.
- `RESET`: Setzt die Sequenz zurück in den Startzustand (xSTART), unabhängig vom aktuellen Zustand.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die Ausführung und liefert die aktuelle Zustandsnummer (`STATE_NR`).
- `EO_S1` bis `EO_S4`: Ereignisausgänge, die aktiviert werden, wenn der entsprechende Zustand (State_01 bis State_04) betreten wird. Liefern jeweils den zugehörigen Datenausgang (`DO_S1` bis `DO_S4`).

### **Daten-Eingänge**
- `DT_S1_S2`: Zeitintervall für den Übergang von State_01 zu State_02 (Typ: `TIME`).
- `DT_S2_S3`: Zeitintervall für den Übergang von State_02 zu State_03 (Typ: `TIME`).
- `DT_S3_S4`: Zeitintervall für den Übergang von State_03 zu State_04 (Typ: `TIME`).
- `DT_S4_S1`: Zeitintervall für den Übergang von State_04 zurück zu State_01 (Typ: `TIME`).

### **Daten-Ausgänge**
- `STATE_NR`: Aktuelle Zustandsnummer (Typ: `SINT`). Werte: 0 (START), 1 (State_01), ..., 4 (State_04).
- `DO_S1` bis `DO_S4`: Boolesche Ausgänge, die im jeweiligen Zustand aktiv sind (Typ: `BOOL`).

### **Adapter**
- `timeOut`: Ein `ATimeOut`-Adapter, der für die zeitgesteuerten Zustandsübergänge verantwortlich ist.

## Funktionsweise
1. **Initialisierung**: Der FB startet im Zustand `xSTART`.
2. **Sequenzstart**: Durch das Ereignis `START_S1` wechselt der FB in `State_01` und aktiviert `DO_S1`.
3. **Zustandsübergänge**: Jeder Zustand wartet das konfigurierte Zeitintervall (`DT_Sx_Sy`) ab, bevor er zum nächsten Zustand wechselt. Die Übergänge erfolgen über den `timeOut`-Adapter.
4. **Zyklus**: Nach `State_04` kehrt der FB automatisch zu `State_01` zurück (`DT_S4_S1`).
5. **Reset**: Das Ereignis `RESET` unterbricht die Sequenz und setzt alle Ausgänge zurück.

## Technische Besonderheiten
- **Zustandsnummerierung**: Die Zustände sind fortlaufend nummeriert (0–4), was eine einfache Überwachung ermöglicht.
- **Zeitsteuerung**: Die Übergangszeiten sind dynamisch konfigurierbar und werden bei jedem Zustandswechsel aktualisiert.
- **Adapter-Nutzung**: Der `timeOut`-Adapter abstrahiert die Zeitsteuerung und vereinfacht die Wiederverwendbarkeit.

## Zustandsübersicht
| Zustand       | Ausgänge               | Übergangsbedingung          |
|---------------|------------------------|-----------------------------|
| `xSTART`      | –                      | `START_S1` → `State_01`     |
| `State_01`    | `DO_S1`, `STATE_NR=1`  | `timeOut.TimeOut` → `State_02` |
| `State_02`    | `DO_S2`, `STATE_NR=2`  | `timeOut.TimeOut` → `State_03` |
| `State_03`    | `DO_S3`, `STATE_NR=3`  | `timeOut.TimeOut` → `State_04` |
| `State_04`    | `DO_S4`, `STATE_NR=4`  | `timeOut.TimeOut` → `State_01` |
| `sRESET`      | Alle Ausgänge zurückgesetzt | Immer → `xSTART`          |

## Anwendungsszenarien
- **Ablaufsteuerungen**: Zyklische Prozesse mit festen Zeitintervallen (z. B. Förderbänder, Beleuchtungssequenzen).
- **Testautomation**: Automatisierte Testabläufe mit zeitgesteuerten Schritten.
- **Maschinensteuerung**: Schrittweise Aktivierung von Aktoren (z. B. Ventile, Motoren).

## Vergleich mit ähnlichen Bausteinen
- **Vorteile**: 
  - Flexibilität durch dynamische Zeitparameter.
  - Klare Zustandsrückmeldung via `STATE_NR`.
- **Nachteile**: 
  - Keine ereignisgesteuerten Übergänge (nur zeitbasiert).
  - Begrenzt auf 4 Zustände (für komplexere Sequenzen sind Erweiterungen nötig).

## Fazit
Der `sequence_T_04_loop` ist ein robuster und einfach konfigurierbarer FB für zyklische, zeitgesteuerte Abläufe. Seine Stärken liegen in der klaren Schnittstelle und der Nutzung des `timeOut`-Adapters für zuverlässige Zeitsteuerung. Für Anwendungen mit mehr Zuständen oder zusätzlichen Triggerbedingungen empfiehlt sich eine Erweiterung des Designs.
