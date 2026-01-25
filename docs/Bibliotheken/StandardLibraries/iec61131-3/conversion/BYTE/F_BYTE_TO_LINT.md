# F_BYTE_TO_LINT

```{index} single: F_BYTE_TO_LINT
```

<img width="1232" height="182" alt="F_BYTE_TO_LINT" src="https://github.com/user-attachments/assets/1ff49b49-3588-44d9-9018-df1b47bce6ea" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_LINT` dient der Konvertierung eines `BYTE`-Wertes in einen `LINT`-Wert. Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_BYTE_TO_LINT](F_BYTE_TO_LINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`BYTE`): Der Eingangswert, der in den `LINT`-Typ konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`LINT`): Der konvertierte Ausgangswert.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Wert am Eingang `IN` vom Typ `BYTE` in den Typ `LINT` konvertiert und am Ausgang `OUT` ausgegeben. Das `CNF`-Ereignis signalisiert den erfolgreichen Abschluss der Konvertierung.

## Technische Besonderheiten
- Der Funktionsblock nutzt die eingebaute Funktion `BYTE_TO_LINT` für die Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsautomaten oder komplexe Algorithmen.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder komplexe Zustandslogik.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `BYTE`-Werte in `LINT`-Werte umgewandelt werden müssen.
- Verwendung in Datenverarbeitungsketten, wo unterschiedliche Datentypen verarbeitet werden.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_LINT` oder `F_DWORD_TO_LINT` bieten ähnliche Funktionalitäten, jedoch für andere Eingangstypen.
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_BYTE_TO_LINT` spezialisiert und optimiert für die Konvertierung von `BYTE` zu `LINT`.

## Fazit
Der `F_BYTE_TO_LINT` Funktionsblock ist ein effizientes und spezialisiertes Werkzeug für die Konvertierung von `BYTE`-Werten in `LINT`-Werte. Seine Einfachheit und direkte Funktionsweise machen ihn zu einer zuverlässigen Wahl in entsprechenden Anwendungsfällen.