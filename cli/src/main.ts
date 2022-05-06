
import commander from 'commander';
import * as C from "./C/parse"
import * as C_declare from "./C/declare"

commander.program.command('gen-c <inDir> <outDir> <moduleName>')
        .description('quick generate pb java')
        .usage("gen-c <inDir> <outDir> <moduleName>")
        .action(function (inDir: string, outDir: string, moduleName: string) {
                C.parse(inDir, outDir, moduleName)
        });

commander.program.command('gen-declare <inFile> <outDir>')
        .description('quick generate pb java')
        .usage("gen-declare <inFile> <outDir>")
        .action(function (inFile: string, outDir: string) {
                C_declare.parse(inFile, outDir)
        });

commander.program.parse(process.argv);