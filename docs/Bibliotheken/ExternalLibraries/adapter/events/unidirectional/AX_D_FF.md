# AX_D_FF

```{index} single: AX_D_FF
```

<img width="1087" height="229" alt="image" src="https://github.com/user-attachments/assets/05b9faba-dff2-41e8-86a4-1031ffe644af" />


![AX_D_FF_ecc](./AX_D_FF_ecc.svg)

* * * * * * * * * *

## Einleitung
Der AX_D_FF ist ein Daten-Latch-Flipflop, das als Basisbaustein in der digitalen Schaltungstechnik dient. Es handelt sich um ein D-Flipflop, das den anliegenden Datenwert speichert und bei bestimmten Ereignissen ausgibt.

![AX_D_FF](AX_D_FF.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereigniseingänge vorhanden

### **Ereignis-Ausgänge**
- Keine direkten Ereignisausgänge vorhanden

### **Daten-Eingänge**
- Keine direkten Dateneingänge vorhanden

### **Daten-Ausgänge**
- Keine direkten Datenausgänge vorhanden

### **Adapter**
- **I** (Socket): Eingangsadapter vom Typ `adapter::types::unidirectional::AX` - Empfängt den zu speichernden Wert
- **Q** (Plug): Ausgangsadapter vom Typ `adapter::types::unidirectional::AX` - Gibt den gespeicherten Wert aus

## Funktionsweise
Das AX_D_FF arbeitet als D-Latch-Flipflop mit drei Zuständen:
- **START**: Initialzustand
- **SET**: Speichert den Eingangswert und gibt ihn aus
- **RESET**: Setzt den Ausgang zurück

Der Algorithmus LATCH kopiert den Eingangswert `I.D1` auf den Ausgang `Q.D1`. Die Zustandsübergänge werden durch den Wert von `I.D1` gesteuert.

## Technische Besonderheiten
- Verwendet unidirektionale Adapter für Ein- und Ausgänge
- Implementiert als Basic Function Block gemäß IEC 61499
- Besitzt eine einfache Latch-Funktionalität ohne Taktung

## Zustandsübersicht
1. **START** → **SET**: Bei Eintreffen von `I.E1` mit `I.D1 = TRUE`
2. **SET** → **RESET**: Wenn `I.D1 = FALSE` wird
3. **RESET** → **SET**: Wenn `I.D1 = TRUE` wird

## Anwendungsszenarien
- Datenspeicherung in Steuerungssystemen
- Zustandsspeicherung in sequenziellen Abläufen
- Signalverzögerung und -pufferung
- Als Grundbaustein für komplexere Flipflop-Schaltungen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu getakteten D-Flipflops arbeitet der AX_D_FF asynchron und speichert den Wert sofort bei Änderung der Eingangsbedingungen. Es handelt sich um ein level-getriggertes anstatt eines flanken-getriggerten Elements.

Vergleich mit [E_D_FF](../../../../StandardLibraries/events/E_D_FF.md)




## 🛠️ Zugehörige Übungen

* [Uebung_170_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_170_AX.md)

## Fazit
Der AX_D_FF bietet eine einfache und effektive Lösung für grundlegende Datenspeicheraufgaben in 4diac-Steuerungssystemen. Seine klare Zustandslogik und die Verwendung standardisierter Adapter machen ihn zu einem zuverlässigen Baustein für verschiedene Anwendungsfälle.