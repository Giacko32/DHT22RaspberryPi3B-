import subprocess
import os

# Source files (aggiungi tutti i .c che vuoi compilare)
source_files = ["tempMeasure.c", "led_matrix_patterns.c", "spi_bb.c", "peripherals.c", "max7219_driver.c", "dht22.c"]
header_files = ["led_matrix_patterns.h", "spi_bb.h", "peripherals.h", "max7219_driver.h", "dht22.h"]

# Nomi file intermedi e finali (per ogni sorgente)
asm_files = []
asm_files_fixed = []
object_files = []

elf_file = "tempMeasure.elf"
disasm_file = "tempMeasure.list"
bin_file = "tempMeasure.bin"
img_file = "kernel7.img"
linker_script = "kernel7.ld"

def run_cmd(cmd):
    print(f"[+] Running: {cmd}")
    subprocess.run(cmd, shell=True, check=True)

def modify_asm_for_baremetal(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    modified_lines = []
    for i, line in enumerate(lines):
        if line.strip().startswith(".size"):
            continue  # Skip .size lines

        if 'main:' in line:
            line = line.replace('main:', '_start:')
            modified_lines.append(line)
            modified_lines.append('    mov sp, #0x80000\n')  # Stack pointer init after _start
        else:
            modified_lines.append(line)

    with open(output_file, 'w') as f:
        f.writelines(modified_lines)

    print(f"[+] Assembly fixed and saved to {output_file}")

def clean_temp_files(files):
    for file in files:
        if os.path.exists(file):
            os.remove(file)
            print(f"[~] Removed temporary file: {file}")

def build():
    try:
        # Step 1: Genera file .s da ogni .c
        for src in source_files:
            asm_file = src.replace(".c", ".s")
            asm_file_fixed = src.replace(".c", "_fixed.s")
            object_file = src.replace(".c", ".o")

            asm_files.append(asm_file)
            asm_files_fixed.append(asm_file_fixed)
            object_files.append(object_file)

            run_cmd(f"arm-none-eabi-gcc -mcpu=cortex-a53 -marm -ffreestanding -nostdlib -S {src} -o {asm_file}")
            modify_asm_for_baremetal(asm_file, asm_file_fixed)
            run_cmd(f"arm-none-eabi-as {asm_file_fixed} -o {object_file}")

        # Step 2: Linka tutti gli object files insieme
        object_files_str = " ".join(object_files)
        run_cmd(f"arm-none-eabi-ld -T {linker_script} {object_files_str} -o {elf_file}")

        # Step 3: Disassemblaggio, objcopy e rinomina
        run_cmd(f"arm-none-eabi-objdump -D {elf_file} > {disasm_file}")
        run_cmd(f"arm-none-eabi-objcopy {elf_file} -O binary {bin_file}")
        run_cmd(f"mv {bin_file} {img_file}")

        print(f"\n[✓] Build completed successfully: {img_file}")

    finally:
        # Pulisci tutti i file temporanei generati
        clean_temp_files(asm_files + asm_files_fixed + object_files + [elf_file, disasm_file])

if __name__ == "__main__":
    build()
